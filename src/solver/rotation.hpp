#pragma once

#include <vector>

#include "tetrominoes.hpp"

namespace tptps {

// clockwise rotation
enum class Rotation : int16_t {
    r0 = 0,
    r90 = 90,
    r180 = 180,
    r270 = 270
};

std::vector<Rotation> get_distinct_tetromino_rotations(Tetromino tetromino);

}  // namespace tptps
