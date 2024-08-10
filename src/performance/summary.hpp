#pragma once

#include <chrono>
#include <vector>

namespace tptps {

void print_summary(const std::chrono::nanoseconds total_duration, const std::vector<std::chrono::nanoseconds::rep>& durations, const std::vector<uint64_t>& function_called, const std::vector<uint64_t>& placements_calculated);

}  // namespace tptps
