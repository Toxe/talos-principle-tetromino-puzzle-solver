#include "board.hpp"

#include <algorithm>
#include <cassert>

namespace tptps {

bool Board::is_empty() const
{
    return std::all_of(grid_.begin(), grid_.end(), [](const auto t) { return t == Tetromino::empty; });
}

bool Board::is_filled() const
{
    return std::none_of(grid_.begin(), grid_.end(), [](const auto t) { return t == Tetromino::empty; });
}

std::string Board::print() const
{
    std::string s;

    for (Square::coordinates_type y = 0; y < height(); ++y) {
        for (Square::coordinates_type x = 0; x < width(); ++x)
            s += static_cast<char>(grid_.at(x, y));

        s += '\n';
    }

    return s;
}

}  // namespace tptps
