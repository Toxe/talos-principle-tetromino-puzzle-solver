#pragma once

#include <vector>

#include "square.hpp"

namespace tptps {

enum class Tetromino : char {
    empty = '.',
    I = 'I',
    O = 'O',
    T = 'T',
    J = 'J',
    L = 'L',
    S = 'S',
    Z = 'Z'
};

// clockwise/compass rotations
enum class Rotation : int16_t {
    r0 = 0,
    r90 = 90,
    r180 = 180,
    r270 = 270
};

std::vector<Rotation> get_distinct_tetromino_orientations(Tetromino tetromino);

}  // namespace tptps
