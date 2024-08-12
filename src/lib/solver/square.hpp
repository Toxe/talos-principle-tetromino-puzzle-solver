#pragma once

#include <string>

#include "../grid/coords.hpp"

namespace tptps {

using Square = Coords<int8_t>;

std::string print_square(Square square);

}  // namespace tptps
