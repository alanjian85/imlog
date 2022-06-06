#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <cstdlib>
#include <string>

#include "level.hpp"

struct Message {
    std::string str;
    std::size_t colorBegin;
    std::size_t colorEnd;
    Level level;
};

#endif