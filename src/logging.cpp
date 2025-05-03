#include <Kai/logging.h>
#include <dpp/dpp.h>
#include <string>

void Kai::createDelMsgLogger(dpp::cluster *bot, dpp::snowflake logChannel) {
	bot->on_message_create([](const dpp::message_create_t &event) {
		dpp::message *msg = new dpp::message;
		*msg = event.msg;
		Kai::messageCache.store(msg);
	});

	bot->on_message_delete([bot, logChannel](const dpp::message_delete_t &event) {
		dpp::message *msg = Kai::messageCache.find(event.id);
		dpp::message *logEmbed;
		dpp::embed delMsgLogggerEmbed = dpp::embed().set_color(dpp::colors::red_blood).set_title("Message Deleted");
		if (!msg) {
			delMsgLogggerEmbed.set_description("Message ID:" + event.id.str())
					.add_field("ERROR", "Message was not cached!");
			logEmbed = new dpp::message(logChannel, delMsgLogggerEmbed);
		} else {

			time_t timestamp = static_cast<time_t>(msg->get_creation_time());
			std::stringstream timestampStr;
			timestampStr << std::put_time(std::gmtime(&timestamp), "%Y-%m-%d %H:%M:%S");

			dpp::user usr = msg->author;
			delMsgLogggerEmbed.set_author(usr.format_username(), "", usr.get_avatar_url())
					.add_field("Message", msg->content)
					.add_field("Channel", dpp::find_channel(msg->channel_id)->get_mention(), true)
					.add_field("Timestamp", timestampStr.str(), true);

			logEmbed = new dpp::message(logChannel, delMsgLogggerEmbed);

			const std::vector<dpp::attachment> msgAttachments = msg->attachments;
			for (const dpp::attachment &attechment: msgAttachments) {
				std::promise<void> donePromise;
				std::future<void> doneFuture = donePromise.get_future();

				attechment.download([&attechment, &logEmbed,
									 &donePromise](const dpp::http_request_completion_t &httpRequestCompletion) {
					logEmbed->add_file(attechment.filename, httpRequestCompletion.body);
					donePromise.set_value();
				});

				doneFuture.get(); // Blocks until attachment is downloaded
			}
		}

		bot->message_create(*logEmbed);
		Kai::messageCache.remove(msg);
	});
}
