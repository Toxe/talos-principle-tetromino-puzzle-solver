#include "solver.hpp"

#include <algorithm>
#include <cassert>

#include "fmt/core.h"

#include "../utility/duration.hpp"
#include "placement_mask.hpp"

namespace tptps {

struct WithPlacedPiece {
    WithPlacedPiece(Board& board, Placement placement) : board_{board}, placement_{placement} { apply_placement(board_, placement); }
    ~WithPlacedPiece() { revert_placement(board_, placement_); }

private:
    Board& board_;
    Placement placement_;
};

template <typename T>
std::vector<T> copy_vector_without_element(const std::vector<T>& src, typename std::vector<T>::const_iterator p)
{
    assert(!src.empty());

    std::vector<T> dst(src.size() - 1);
    const auto dst_end = std::copy(src.cbegin(), p, dst.begin());
    std::copy(p + 1, src.cend(), dst_end);

    return dst;
}

std::optional<Board> solve_puzzle(Board& board, std::vector<Tetromino> tetrominoes, SolverStatus& status)
{
    status.add_function_called();

    for (auto p = tetrominoes.cbegin(); p != tetrominoes.cend(); ++p) {
        const auto placements = find_all_possible_placements(board, *p);
        const std::vector<Tetromino> new_list = copy_vector_without_element(tetrominoes, p);
        status.add_placements_calculated(placements.size());

        for (const Placement placement : placements) {
            const WithPlacedPiece with_owner_of_square{board, placement};

            if (board.is_filled()) {
                status.stop();
                return board;
            }

            if (const auto returned_board = solve_puzzle(board, new_list, status); returned_board)
                return *returned_board;
        }
    }

    return std::nullopt;
}

std::vector<Placement> find_all_possible_placements(const Board& board, const Tetromino tetromino)
{
    const auto distinct_rotations = get_distinct_tetromino_rotations(tetromino);
    std::vector<Placement> placements;

    for (const auto rotation : {Rotation::r0, Rotation::r90, Rotation::r180, Rotation::r270})
        if (distinct_rotations.has(rotation))
            placements.append_range(find_possible_placements_for_rotation(board, tetromino, rotation));

    return placements;
}

std::vector<Placement> find_possible_placements_for_rotation(const Board& board, const Tetromino tetromino, const Rotation rotation)
{
    const auto mask = get_tetromino_placement_mask(tetromino, rotation);
    std::vector<Placement> placements;

    if (board.height() > board.width()) {
        for (Square::coordinates_type x = 0; x <= board.width() - mask.width(); ++x) {
            for (Square::coordinates_type y = 0; y <= board.height() - mask.height(); ++y) {
                const Placement placement{{x, y}, tetromino, rotation};

                if (is_possible_placement(board, placement, mask)) {
                    placements.push_back(placement);
                    break;
                }
            }
        }
    } else {
        for (Square::coordinates_type y = 0; y <= board.height() - mask.height(); ++y) {
            for (Square::coordinates_type x = 0; x <= board.width() - mask.width(); ++x) {
                const Placement placement{{x, y}, tetromino, rotation};

                if (is_possible_placement(board, placement, mask)) {
                    placements.push_back(placement);
                    break;
                }
            }
        }
    }

    return placements;
}

}  // namespace tptps
