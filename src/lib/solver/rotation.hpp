#pragma once

#include <vector>

#include "tetrominoes.hpp"

namespace tptps {

// clockwise rotation
enum class Rotation : char {
    r0,
    r90,
    r180,
    r270
};

std::vector<Rotation> get_distinct_tetromino_rotations(Tetromino tetromino);

}  // namespace tptps
