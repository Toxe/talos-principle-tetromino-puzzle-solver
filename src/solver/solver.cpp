#include "solver.hpp"

#include "placement_mask.hpp"

namespace tptps {

std::optional<Board> solve_puzzle(Board board, std::vector<Tetromino> tetrominoes, SolverStats& stats)
{
    while (!tetrominoes.empty()) {
        const Tetromino t = tetrominoes.back();
        tetrominoes.pop_back();

        const auto placements = get_all_possible_placements(board, t);

        stats.possible_placements_calculated += placements.size();

        for (const auto& placement : placements) {
            Board tmp_board = board;
            tmp_board.place(placement);

            ++stats.placements_checked;

            if (tmp_board.is_finished())
                return tmp_board;

            const auto returned_board = solve_puzzle(tmp_board, tetrominoes, stats);

            if (returned_board.has_value())
                return *returned_board;
        }
    }

    return std::nullopt;
}

std::vector<Placement> get_all_possible_placements(const Board& board, const Tetromino tetromino)
{
    const auto orientations = get_distinct_tetromino_orientations(tetromino);
    std::vector<Placement> placements;

    for (const auto rotation : orientations)
        placements.append_range(find_possible_placements(board, tetromino, rotation));

    return placements;
}

std::vector<Placement> find_possible_placements(const Board& board, const Tetromino tetromino, const Rotation rotation)
{
    std::vector<Placement> placements;
    const auto mask = get_tetromino_placement_mask(tetromino, rotation);

    for (Square::coordinates_type y = 0; y <= board.height() - mask.height(); ++y) {
        for (Square::coordinates_type x = 0; x <= board.width() - mask.width(); ++x) {
            const Placement placement{{x, y}, tetromino, rotation};

            if (board.can_place(placement, mask))
                placements.push_back(placement);
        }
    }

    return placements;
}

}  // namespace tptps
