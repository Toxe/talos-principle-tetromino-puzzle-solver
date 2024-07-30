#pragma once

#include <chrono>
#include <string>

namespace tptps {

struct SolverStats {
    std::chrono::steady_clock::time_point time_begin = std::chrono::steady_clock::now();
    uint64_t placements_checked = 0;
    uint64_t possible_placements_calculated = 0;

    std::string print() const;
};

}  // namespace tptps
