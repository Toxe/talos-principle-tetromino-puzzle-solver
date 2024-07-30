#include "stats.hpp"

#include "fmt/core.h"

using namespace std::literals::chrono_literals;

namespace tptps {

std::string format_duration(std::chrono::nanoseconds dur)
{
    if (dur < 10us)
        return fmt::format("{:.3f} us", std::chrono::duration_cast<std::chrono::duration<float, std::micro>>(dur).count());
    else
        return fmt::format("{:.3f} ms", std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(dur).count());
}

std::string tptps::SolverStats::print() const
{
    return fmt::format("checks: {:>8}, possible placements: {:>8}, {:>12}", placements_checked, possible_placements_calculated, format_duration(std::chrono::steady_clock::now() - time_begin));
}

}  // namespace tptps
