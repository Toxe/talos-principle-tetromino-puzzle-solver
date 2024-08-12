#pragma once

#include <chrono>
#include <string>

namespace tptps {

class SolverStatus {
public:
    SolverStatus(const std::string& progress_line_prefix = "", const bool show_progress = true)
        : show_progress_{show_progress && !progress_line_prefix.empty()}, progress_line_prefix_{progress_line_prefix} { }

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
    void print_progress(const std::string& suffix = "");
    [[nodiscard]] std::string build_progress_line(const std::string& suffix = "") const;

private:
    bool show_progress_;
    int previous_progress_line_length_ = 0;
    std::chrono::steady_clock::time_point time_last_progress_;
    std::string progress_line_prefix_;

    [[nodiscard]] bool should_print_progress_line() const;

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
