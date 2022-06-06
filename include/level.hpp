#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <stdexcept>

#include <spdlog/common.h>

enum class Level {
    trace    = spdlog::level::trace,
    debug    = spdlog::level::debug,
    info     = spdlog::level::info,
    warning  = spdlog::level::warn,
    error    = spdlog::level::err,
    critical = spdlog::level::critical
};

#endif