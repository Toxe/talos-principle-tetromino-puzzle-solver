#pragma once

#include "tetrominoes.hpp"

namespace tptps {

// clockwise rotation
enum class Rotation : char {
    r0,
    r90,
    r180,
    r270
};

class DistinctTetrominoRotations {
public:
    DistinctTetrominoRotations(const bool r0 = false, const bool r90 = false, const bool r180 = false, const bool r270 = false)
        : r0_{r0}, r90_{r90}, r180_{r180}, r270_{r270} { }

    [[nodiscard]] bool has(Rotation rotation) const;

private:
    bool r0_;
    bool r90_;
    bool r180_;
    bool r270_;
};

DistinctTetrominoRotations get_distinct_tetromino_rotations(Tetromino tetromino);

}  // namespace tptps
