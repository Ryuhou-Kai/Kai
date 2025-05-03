#include <dpp/dpp.h>
#include <string>

#include <Kai/config.h>
#include <Kai/logging.h>
#include <Kai/miscellaneous.h>

#if DEBUG_VALUE // This is the Token for testing replace with your own bot Token nad the logger channel id!
const std::string BOT_TOKEN = "MTM1NjY1NzIwMTkwNDYxOTc4Mg.GHSer4.suQ1pyJg5oCRjXqGy7oABmZRBYCzJLxGbGj0uY";
const dpp::snowflake LOG_CHANNEL_ID = 1367473662172598412;
#else // This is the Token for the Bot on the main discord server
const std::string BOT_TOKEN = "MTM1NTUzNzM5MTU5ODgyOTU3Ng.G2LXKA.A0jNHaGhZ1yU0zvTxI32kMhvMO-gMO4J2rZypg";
const dpp::snowflake LOG_CHANNEL_ID = 1366138544690823259;
#endif

int main() {
	dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);

	bot.on_log(dpp::utility::cout_logger());

    Kai::createDelMsgLogger(&bot, LOG_CHANNEL_ID);

    Kai::createCatRepl(&bot);

	bot.on_ready([&bot](const dpp::ready_t &event) {
		if (dpp::run_once<struct register_bot_commands>()) {
			// bot.global_command_create(dpp::slashcommand("embed", "Sendatestembed!", bot.me.id));
		}
	});

	bot.start();

	return 0;
}
