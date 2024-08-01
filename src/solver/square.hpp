#pragma once

#include <string>

#include "../grid/coords.hpp"

namespace tptps {

using Square = Coords<int16_t>;

std::string print_square(Square square);

}  // namespace tptps
