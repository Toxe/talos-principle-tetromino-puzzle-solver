#pragma once

#include "board.hpp"
#include "placement_mask.hpp"
#include "square.hpp"
#include "tetrominoes.hpp"

namespace tptps {

struct Placement {
    Square coords;
    Tetromino tetromino;
    Rotation rotation;

    auto operator<=>(const Placement& rhs) const = default;
};

bool is_possible_placement(const Board& board, Placement placement, const PlacementMask& mask);
void apply_placement(Board& board, Placement placement);
void revert_placement(Board& board, Placement placement);

}  // namespace tptps
