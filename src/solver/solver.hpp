#pragma once

#include <optional>
#include <vector>

#include "board.hpp"
#include "tetrominoes.hpp"

namespace tptps {

struct SolverStats {
    uint64_t placements_checked = 0;
    uint64_t possible_placements_calculated = 0;
};

std::optional<Board> solve_puzzle(Board board, std::vector<Tetromino> tetrominoes, SolverStats& stats);
std::vector<Placement> get_all_possible_placements(const Board& board, Tetromino t);
std::vector<Placement> find_possible_placements(const Board& board, Tetromino t, Rotation rotation);

}  // namespace tptps
