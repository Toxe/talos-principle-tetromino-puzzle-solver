#include "tetrominoes.hpp"

#include <cassert>

namespace tptps {

std::vector<Rotation> get_distinct_tetromino_orientations(Tetromino tetromino)
{
    assert(tetromino != Tetromino::empty && tetromino != Tetromino::unknown);

    switch (tetromino) {
        case Tetromino::I: return {Rotation::r0, Rotation::r90}; break;
        case Tetromino::O: return {Rotation::r0}; break;
        case Tetromino::T: return {Rotation::r0, Rotation::r90, Rotation::r180, Rotation::r270}; break;
        case Tetromino::J: return {Rotation::r0, Rotation::r90, Rotation::r180, Rotation::r270}; break;
        case Tetromino::L: return {Rotation::r0, Rotation::r90, Rotation::r180, Rotation::r270}; break;
        case Tetromino::S: return {Rotation::r0, Rotation::r90}; break;
        case Tetromino::Z: return {Rotation::r0, Rotation::r90}; break;
    }
}

}  // namespace tptps
