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

void SolverStatus::print_progress(const std::string& suffix)
{
    const std::string msg = build_progress_line(suffix);

    fmt::print("\r{}", msg);

    previous_progress_line_length_ = str_mb_length(msg);
    time_last_progress_ = std::chrono::steady_clock::now();
}

std::string SolverStatus::build_progress_line(const std::string& suffix) const
{
    std::string msg = fmt::format("{} {:>11} (calls: {}, calculations: {}){}", progress_line_prefix_, print_duration(duration()), function_called_, placements_calculated_, suffix);
    const int msg_length = str_mb_length(msg);

    if (msg_length < previous_progress_line_length_)
        msg += std::string(previous_progress_line_length_ - msg_length, ' ');

    return msg;
}

bool SolverStatus::should_print_progress_line() const
{
    return show_progress_ && is_running_ && std::chrono::steady_clock::now() - time_last_progress_ >= 100ms;
}

void SolverStatus::update(const uint64_t add_function_called, const uint64_t add_placements_calculated)
{
    if (!is_running_)
        start();

    function_called_ += add_function_called;
    placements_calculated_ += add_placements_calculated;

    if (should_print_progress_line())
        print_progress();
}

}  // namespace tptps
