#include "solver.hpp"

#include <cassert>

#include "placement_mask.hpp"

namespace tptps {

struct WithPlacedPiece {
    WithPlacedPiece(Board& board, Placement placement) : board_{board}, placement_{placement} { board_.place(placement); }
    ~WithPlacedPiece() { board_.revert_placement(placement_); }

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

std::optional<Board> solve_puzzle(Board& board, std::vector<Tetromino> tetrominoes, SolverStats& stats)
{
    for (auto p = tetrominoes.cbegin(); p != tetrominoes.cend(); ++p) {
        const auto placements = find_all_possible_placements(board, *p);
        const std::vector<Tetromino> new_list = copy_vector_without_element(tetrominoes, p);

        stats.possible_placements_calculated += placements.size();

        for (const auto& placement : placements) {
            const WithPlacedPiece with_owner_of_square{board, placement};
            ++stats.placements_checked;

            if (board.is_finished())
                return board;

            if (const auto returned_board = solve_puzzle(board, new_list, stats); returned_board)
                return *returned_board;
        }
    }

    return std::nullopt;
}

std::vector<Placement> find_all_possible_placements(const Board& board, const Tetromino tetromino)
{
    const auto orientations = get_distinct_tetromino_orientations(tetromino);
    std::vector<Placement> placements;

    for (const auto rotation : orientations)
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

                if (board.can_place(placement, mask)) {
                    placements.push_back(placement);
                    break;
                }
            }
        }
    } else {
        for (Square::coordinates_type y = 0; y <= board.height() - mask.height(); ++y) {
            for (Square::coordinates_type x = 0; x <= board.width() - mask.width(); ++x) {
                const Placement placement{{x, y}, tetromino, rotation};

                if (board.can_place(placement, mask)) {
                    placements.push_back(placement);
                    break;
                }
            }
        }
    }

    return placements;
}

}  // namespace tptps
