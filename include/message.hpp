#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>

#include <spdlog/spdlog.h>

struct Message {
    Message(const std::string& str, const spdlog::details::log_msg& msg) {
        head = str.substr(0, msg.color_range_start);
        body = str.substr(msg.color_range_start, msg.color_range_end - msg.color_range_start);
        foot = str.substr(msg.color_range_end);
        level = msg.level;
    }

    std::string head;
    std::string body;
    std::string foot;
    spdlog::level::level_enum level;
};

#endif