#include "solver_status.hpp"

#include "fmt/core.h"

#include "../utility/duration.hpp"
#include "../utility/str.hpp"

using namespace std::literals::chrono_literals;

namespace tptps {

void SolverStatus::start()
{
    if (!is_running_) {
        is_running_ = true;
        time_started_ = std::chrono::steady_clock::now();
    }
}

void SolverStatus::stop()
{
    if (is_running_) {
        is_running_ = false;
        time_stopped_ = std::chrono::steady_clock::now();
    }
}

std::chrono::nanoseconds SolverStatus::duration() const
{
    if (is_running_)
        return std::chrono::steady_clock::now() - time_started_;
    else
        return time_stopped_ - time_started_;
}

void SolverStatus::print_log_message(const std::string& suffix)
{
    if (!logging_enabled_)
        return;

    const std::string msg = build_log_message(suffix);

    fmt::print("\r{}", msg);

    previous_log_message_length_ = str_mb_length(msg);
    time_last_log_ = std::chrono::steady_clock::now();
}

std::string SolverStatus::build_log_message(const std::string& suffix) const
{
    if (!logging_enabled_)
        return "";

    std::string msg = fmt::format("{} {:>11} (calls: {}, calculations: {}){}", log_prefix_, print_duration(duration()), function_called_, placements_calculated_, suffix);
    const int msg_length = str_mb_length(msg);

    if (msg_length < previous_log_message_length_)
        msg += std::string(previous_log_message_length_ - msg_length, ' ');

    return msg;
}

bool SolverStatus::should_print_log_message() const
{
    return logging_enabled_ && is_running_ && std::chrono::steady_clock::now() - time_last_log_ >= 100ms;
}

void SolverStatus::update(const uint64_t add_function_called, const uint64_t add_placements_calculated)
{
    if (!is_running_)
        start();

    function_called_ += add_function_called;
    placements_calculated_ += add_placements_calculated;

    if (should_print_log_message())
        print_log_message();
}

}  // namespace tptps
