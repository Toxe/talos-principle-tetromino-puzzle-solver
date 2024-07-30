#pragma once

#include <string_view>
#include <vector>

#include "../grid/grid.hpp"
#include "tetrominoes.hpp"

namespace tptps {

using PlacementMask = Grid<int8_t, Square>;

PlacementMask placement_mask_from_string(const std::vector<std::string_view>& data);
PlacementMask get_tetromino_placement_mask(Tetromino tetromino, Rotation rotation);

}  // namespace tptps
