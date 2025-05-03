#pragma once

#include <dpp/dpp.h>

namespace Kai {
    static dpp::cache<dpp::message> messageCache;

    void createDelMsgLogger(dpp::cluster* bot, dpp::snowflake logChannel);
}