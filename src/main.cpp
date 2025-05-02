#include <dpp/dpp.h>
#include <string>

#include "config.h"
// PLS READ!!!!!!!!!!!!!!!!
#if DEBUG_VALUE // This is the Token for testing replace with your own bot Token nad the logger channel id!
const std::string BOT_TOKEN = "MTM1NjY1NzIwMTkwNDYxOTc4Mg.GHSer4.suQ1pyJg5oCRjXqGy7oABmZRBYCzJLxGbGj0uY";
const dpp::snowflake LOG_CHANNEL_ID = 1367473662172598412;
#else // This is the Token for the Bot on the discord server
const std::string BOT_TOKEN = "MTM1NTUzNzM5MTU5ODgyOTU3Ng.G2LXKA.A0jNHaGhZ1yU0zvTxI32kMhvMO-gMO4J2rZypg";
const dpp::snowflake LOG_CHANNEL_ID = 1366138544690823259;
#endif

int main() {
	dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);

	bot.on_log(dpp::utility::cout_logger());

	dpp::cache<dpp::message> message_cache;

	bot.on_message_create([&bot, &message_cache](const dpp::message_create_t &event) {
		if (event.msg.content.find("!cat") != std::string::npos) {
			bot.request("https://cataas.com/cat", dpp::m_get,
						[event](const dpp::http_request_completion_t &httpRequestCompletion) {
							dpp::message msg("Here's your cat: /ᐠ-˕-マⳊ");

							if (httpRequestCompletion.status == 200)
								msg.add_file("cat.png", httpRequestCompletion.body);

							event.reply(msg, true);
						});
		}

		dpp::message *msg = new dpp::message;
		*msg = event.msg;
		message_cache.store(msg);
	});

	bot.on_message_delete([&bot, &message_cache](const dpp::message_delete_t &event) {

		dpp::message *msg = message_cache.find(event.id);

		time_t timestamp = static_cast<time_t>(msg->get_creation_time());
		std::stringstream timestampStr;
		timestampStr << std::put_time(std::gmtime(&timestamp), "%Y-%m-%d %H:%M:%S");

		dpp::message *logEmbed;
		dpp::embed delMsgLogggerEmbed = dpp::embed().set_color(dpp::colors::red_blood).set_title("Message Deleted");
		if (!msg) {
			delMsgLogggerEmbed.set_description("Message ID:" + event.id.str())
					.add_field("ERROR", "Message was not cached!");
			logEmbed = new dpp::message(LOG_CHANNEL_ID, delMsgLogggerEmbed);
		} else {
			dpp::user usr = msg->author;
			delMsgLogggerEmbed.set_author(usr.format_username(), "", usr.get_avatar_url())
					.add_field("Message", msg->content)
					.add_field("Channel", msg->channel_id.str(), true)
					.add_field("Timestamp", timestampStr.str(), true);

			const std::vector<dpp::attachment> msgAttachments = msg->attachments;
			logEmbed = new dpp::message(LOG_CHANNEL_ID, delMsgLogggerEmbed);
			for (const dpp::attachment &attechment: msgAttachments) {
				std::promise<void> donePromise;
				std::future<void> doneFuture = donePromise.get_future();

				attechment.download([&bot, &attechment, &logEmbed,
									 &donePromise](const dpp::http_request_completion_t &httpRequestCompletion) {
					logEmbed->add_file(attechment.filename, httpRequestCompletion.body);
					donePromise.set_value();
				});

				doneFuture.get(); // Blocks until asyncFunction calls set_value()
			}
		}
		bot.message_create(*logEmbed);
		message_cache.remove(msg);
	});

	bot.on_ready([&bot](const dpp::ready_t &event) {
		if (dpp::run_once<struct register_bot_commands>()) {
			// bot.global_command_create(dpp::slashcommand("embed", "Sendatestembed!", bot.me.id));
		}
	});

	bot.start();

	return 0;
}
