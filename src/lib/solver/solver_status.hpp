#pragma once

#include <chrono>
#include <string>

namespace tptps {

class SolverStatus {
public:
    SolverStatus(const std::string& log_prefix = "", const bool show_progress = true)
        : show_progress_{show_progress && !log_prefix.empty()}, log_prefix_{log_prefix} { }

public:
    void start();
    void stop();
    [[nodiscard]] bool is_running() const { return is_running_; }
    [[nodiscard]] std::chrono::nanoseconds duration() const;

private:
    std::chrono::steady_clock::time_point time_started_;
    std::chrono::steady_clock::time_point time_stopped_;
    bool is_running_ = false;

public:
    void print_log_message(const std::string& suffix = "");
    [[nodiscard]] std::string build_log_message(const std::string& suffix = "") const;

private:
    bool show_progress_;
    int previous_log_message_length_ = 0;
    std::chrono::steady_clock::time_point time_last_log_;
    std::string log_prefix_;

    [[nodiscard]] bool should_print_log_message() const;

public:
    void add_function_called() { return update(1, 0); }
    void add_placements_calculated(const uint64_t add) { return update(0, add); }

    [[nodiscard]] uint64_t function_called() const { return function_called_; }
    [[nodiscard]] uint64_t placements_calculated() const { return placements_calculated_; }

private:
    uint64_t function_called_ = 0;
    uint64_t placements_calculated_ = 0;

    void update(uint64_t add_function_called, uint64_t add_placements_calculated);
};

}  // namespace tptps
