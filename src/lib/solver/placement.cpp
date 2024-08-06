#include "placement.hpp"

#include <cassert>

namespace tptps {

bool is_possible_placement(const Board& board, const Placement placement, const PlacementMask& mask)
{
    for (Square::coordinates_type y = 0; y < mask.height(); ++y) {
        for (Square::coordinates_type x = 0; x < mask.width(); ++x) {
            const Square square = placement.coords + Square{x, y};

            if (square.x >= board.width() || square.y >= board.height())
                return false;

            if (mask.at({x, y}) && !board.is_empty_square(square))
                return false;
        }
    }

    return true;
}

void apply_placement(Board& board, const Placement placement)
{
    const auto mask = get_tetromino_placement_mask(placement.tetromino, placement.rotation);

    for (Square::coordinates_type y = 0; y < mask.height(); ++y) {
        for (Square::coordinates_type x = 0; x < mask.width(); ++x) {
            const Square square = placement.coords + Square{x, y};

            if (mask.at({x, y})) {
                assert(board.is_empty_square(square));
                board.at(square) = placement.tetromino;
            }
        }
    }
}

void revert_placement(Board& board, const Placement placement)
{
    const auto mask = get_tetromino_placement_mask(placement.tetromino, placement.rotation);

    for (Square::coordinates_type y = 0; y < mask.height(); ++y) {
        for (Square::coordinates_type x = 0; x < mask.width(); ++x) {
            const Square square = placement.coords + Square{x, y};

            if (mask.at({x, y})) {
                assert(!board.is_empty_square(square));
                board.at(square) = Tetromino::empty;
            }
        }
    }
}

}  // namespace tptps
