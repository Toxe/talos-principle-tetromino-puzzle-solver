#include "rotation.hpp"

#include <cassert>
#include <stdexcept>
#include <utility>

namespace tptps {

DistinctTetrominoRotations get_distinct_tetromino_rotations(Tetromino tetromino)
{
    assert(tetromino != Tetromino::empty);

    switch (tetromino) {
        case Tetromino::I: return DistinctTetrominoRotations{true, true}; break;
        case Tetromino::O: return DistinctTetrominoRotations{true}; break;
        case Tetromino::T: return DistinctTetrominoRotations{true, true, true, true}; break;
        case Tetromino::J: return DistinctTetrominoRotations{true, true, true, true}; break;
        case Tetromino::L: return DistinctTetrominoRotations{true, true, true, true}; break;
        case Tetromino::S: return DistinctTetrominoRotations{true, true}; break;
        case Tetromino::Z: return DistinctTetrominoRotations{true, true}; break;
        case Tetromino::empty: throw std::runtime_error{"invalid tetromino"};
    }

    std::unreachable();
}

bool DistinctTetrominoRotations::has(const Rotation rotation) const
{
    switch (rotation) {
        case Rotation::r0: return r0_; break;
        case Rotation::r90: return r90_; break;
        case Rotation::r180: return r180_; break;
        case Rotation::r270: return r270_; break;
    }

    std::unreachable();
}

}  // namespace tptps
