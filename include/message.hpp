#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <cstdlib>
#include <string>

#include <spdlog/common.h>

struct Message {
    Message(const std::string& str_, std::size_t colorBegin_, std::size_t colorEnd_, 
        spdlog::level::level_enum level_) {
        head = str_.substr(0, colorBegin_);
        body = str_.substr(colorBegin_, colorEnd_ - colorBegin_);
        foot = str_.substr(colorEnd_);
        level = level_;
    }

    std::string head;
    std::string body;
    std::string foot;
    spdlog::level::level_enum level;
};

#endif