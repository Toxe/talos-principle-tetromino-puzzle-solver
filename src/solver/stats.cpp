#include "stats.hpp"

#include "fmt/core.h"

using namespace std::literals::chrono_literals;

namespace tptps {

std::string format_duration(std::chrono::nanoseconds dur)
{
    if (dur < 1000ns)
        return fmt::format("{:.3f} ns", std::chrono::duration_cast<std::chrono::duration<float, std::nano>>(dur).count());
    else if (dur < 1000us)
        return fmt::format("{:.3f} μs", std::chrono::duration_cast<std::chrono::duration<float, std::micro>>(dur).count());
    else if (dur < 1000ms)
        return fmt::format("{:.3f} ms", std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(dur).count());
    else
        return fmt::format("{:.3f} s ", std::chrono::duration_cast<std::chrono::duration<float>>(dur).count());
}

std::string tptps::SolverStats::print() const
{
    return fmt::format("{:>12} | {:>19} | {:>12}", placements_checked, possible_placements_calculated, format_duration(std::chrono::steady_clock::now() - time_begin));
}

}  // namespace tptps
