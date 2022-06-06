#ifndef LOG_SINK_HPP
#define LOG_SINK_HPP

#include <spdlog/sinks/base_sink.h>

#include "log.hpp"

template <typename Mutex>
class LogSink : public spdlog::sinks::base_sink<Mutex> {
public:
    LogSink(Log& log) : m_Log(log) {

    }
protected:
    void sink_it_(const spdlog::details::log_msg& msg) override {
        spdlog::memory_buf_t formatted;
        spdlog::sinks::base_sink<Mutex>::formatter_->format(msg, formatted);
        m_Log.addLog({fmt::to_string(formatted), msg.color_range_start, msg.color_range_end, Level{msg.level}});
    }

    void flush_() override {
        
    }
private:
    Log& m_Log;
};

#include <spdlog/details/null_mutex.h>
#include <mutex>
using LogSink_mt = LogSink<std::mutex>;
using LogSink_st = LogSink<spdlog::details::null_mutex>;

#endif