#include "board.hpp"

#include <algorithm>
#include <cassert>

#include "placement_mask.hpp"

namespace tptps {

bool Board::is_finished() const
{
    return std::none_of(grid_.begin(), grid_.end(), [](const auto t) { return t == Tetromino::empty; });
}

bool Board::can_place(const Placement placement) const
{
    const auto mask = get_tetromino_placement_mask(placement.tetromino, placement.rotation);

    for (Square::coordinates_type y = 0; y < mask.height(); ++y) {
        for (Square::coordinates_type x = 0; x < mask.width(); ++x) {
            Square square = placement.coords + Square{x, y};

            if (square.x >= width() || square.y >= height())
                return false;

            if (mask.at({x, y}) && !is_empty_square(square))
                return false;
        }
    }

    return true;
}

void Board::place(const Placement placement)
{
    const auto mask = get_tetromino_placement_mask(placement.tetromino, placement.rotation);

    for (Square::coordinates_type y = 0; y < mask.height(); ++y) {
        for (Square::coordinates_type x = 0; x < mask.width(); ++x) {
            Square square = placement.coords + Square{x, y};

            if (mask.at({x, y})) {
                assert(is_empty_square(square));
                grid_.at(square) = placement.tetromino;
            }
        }
    }
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
