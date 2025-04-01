#include <dpp/dpp.h>
#include <string>

const std::string BOT_TOKEN = "MTM1NTUzNzM5MTU5ODgyOTU3Ng.G2LXKA.A0jNHaGhZ1yU0zvTxI32kMhvMO-gMO4J2rZypg";

int main() {
	dpp::cluster bot(BOT_TOKEN, dpp::i_default_intents | dpp::i_message_content);

	bot.on_log(dpp::utility::cout_logger());
	/*Theeventisfiredwhensomeoneissuesyourcommands*/
	bot.on_slashcommand([&bot](const dpp::slashcommand_t &event) {
		/*Checkwhichcommandtheyran*/
		if (event.command.get_command_name() == "embed") {
			/*Createanembed*/
			dpp::embed embed = dpp::embed()
									   .set_color(dpp::colors::sti_blue)
									   .set_title("Somename")
									   .set_url("https://dpp.dev/")
									   .set_author("Somename", "https://dpp.dev/", "https://dpp.dev/DPP-Logo.png")
									   .set_description("Somedescriptionhere")
									   .set_thumbnail("https://dpp.dev/DPP-Logo.png")
									   .add_field("Regularfieldtitle", "Somevaluehere")
									   .add_field("Inlinefieldtitle", "Somevaluehere", true)
									   .add_field("Inlinefieldtitle", "Somevaluehere", true)
									   .set_image("https://dpp.dev/DPP-Logo.png")
									   .set_footer(dpp::embed_footer()
														   .set_text("Somefootertexthere")
														   .set_icon("https://dpp.dev/DPP-Logo.png"))
									   .set_timestamp(time(0));

			/*Createamessagewiththecontentasournewembed.*/
			dpp::message msg(event.command.channel_id, embed);

			/*Replytotheuserwiththemessage,containingourembed.*/
			event.reply(msg);
		}
	});

	bot.on_message_create([&bot](const dpp::message_create_t &event) {
		/*Seeifthemessagecontainsthephrasewewanttocheckfor.
		 *Ifthere'satleastasinglematch,wereplyandsayit'snotallowed.
		 */
		if (event.msg.content.find("!cat") != std::string::npos) {
			bot.request("https://cataas.com/cat", dpp::m_get,
						[event](const dpp::http_request_completion_t &httpRequestCompletion) {
							/*Createamessage*/
							dpp::message msg("Here'syourcat: /ᐠ-˕-マⳊ");

							/*Attachtheimagetothemessage,onlyonsuccess(Code200).*/
							if (httpRequestCompletion.status == 200)
								msg.add_file("cat.png", httpRequestCompletion.body);

							/*Sendthemessage,withourattachment.*/
							event.reply(msg, true);
						});
		}
	});

	bot.on_ready([&bot](const dpp::ready_t &event) {
		if (dpp::run_once<struct register_bot_commands>()) {
			/*Createandregisteracommandwhenthebotisready*/
			bot.global_command_create(dpp::slashcommand("embed", "Sendatestembed!", bot.me.id));
		}
	});

	bot.start();

	return 0;
}
