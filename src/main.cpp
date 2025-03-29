#include <dpp/dpp.h>
#include <string>

const std::string BOT_TOKEN = "MTM1NTUzNzM5MTU5ODgyOTU3Ng.G2LXKA.A0jNHaGhZ1yU0zvTxI32kMhvMO-gMO4J2rZypg";

int main() {
    dpp::cluster bot(BOT_TOKEN);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "ping") {
            event.reply("Pong!");
        }
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
        }
    });

    bot.start(dpp::st_wait);
}