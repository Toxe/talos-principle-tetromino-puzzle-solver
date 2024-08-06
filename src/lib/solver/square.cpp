#include "square.hpp"

#include "fmt/core.h"

namespace tptps {

std::string print_square(const Square square)
{
    return fmt::format("{}×{}", square.x, square.y);
}

}  // namespace tptps
