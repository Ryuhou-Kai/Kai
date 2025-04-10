#include <dpp/dpp.h>
#include <string>

#include "config.h"
//PLS READ!!!!!!!!!!!!!!!!
#if DEBUG_VALUE // This is the Token for testing replace with your own bot Token!
const std::string BOT_TOKEN = "MTM1NjY1NzIwMTkwNDYxOTc4Mg.GHSer4.suQ1pyJg5oCRjXqGy7oABmZRBYCzJLxGbGj0uY";
#else// This is the Token for the Bot on the discord server
const std::string BOT_TOKEN = "MTM1NTUzNzM5MTU5ODgyOTU3Ng.G2LXKA.A0jNHaGhZ1yU0zvTxI32kMhvMO-gMO4J2rZypg";
#endif

int main() {
	dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);

	bot.on_log(dpp::utility::cout_logger());

	bot.on_message_create([&bot](const dpp::message_create_t &event) {
		if (event.msg.content.find("!cat") != std::string::npos) {
			bot.request("https://cataas.com/cat", dpp::m_get,
						[event](const dpp::http_request_completion_t &httpRequestCompletion) {
							dpp::message msg("Here's your cat: /ᐠ-˕-マⳊ");

							if (httpRequestCompletion.status == 200)
								msg.add_file("cat.png", httpRequestCompletion.body);

							event.reply(msg, true);
						});
		}
	});

	bot.on_ready([&bot](const dpp::ready_t &event) {
		if (dpp::run_once<struct register_bot_commands>()) {
			bot.global_command_create(dpp::slashcommand("embed", "Sendatestembed!", bot.me.id));
		}
	});

	bot.start();

	return 0;
}
