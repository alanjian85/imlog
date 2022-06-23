#ifndef LOG_SINK_HPP
#define LOG_SINK_HPP

#include <spdlog/sinks/base_sink.h>

#include "log.hpp"

template <typename Mutex>
class LogSink : public spdlog::sinks::base_sink<Mutex> {
public:
    LogSink(Log& log) : log(log) {

    }
protected:
    void sink_it_(const spdlog::details::log_msg& msg) override {
        spdlog::memory_buf_t formatted;
        spdlog::sinks::base_sink<Mutex>::formatter_->format(msg, formatted);
        log.addMessage(Message(fmt::to_string(formatted), msg));
    }

    void flush_() override {
        
    }
private:
    Log& log;
};

#include <spdlog/details/null_mutex.h>
#include <mutex>
using LogSink_mt = LogSink<std::mutex>;
using LogSink_st = LogSink<spdlog::details::null_mutex>;

#endif