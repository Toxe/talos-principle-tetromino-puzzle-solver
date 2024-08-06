#pragma once

#include <chrono>
#include <string>

namespace tptps {

std::string print_duration(std::chrono::nanoseconds dur);

}  // namespace tptps
