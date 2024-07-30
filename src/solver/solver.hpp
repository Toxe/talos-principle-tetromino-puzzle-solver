#pragma once

#include <optional>
#include <vector>

#include "board.hpp"
#include "stats.hpp"
#include "tetrominoes.hpp"

namespace tptps {

std::optional<Board> solve_puzzle(Board board, std::vector<Tetromino> tetrominoes, SolverStats& stats);
std::vector<Placement> get_all_possible_placements(const Board& board, Tetromino t);
std::vector<Placement> find_possible_placements(const Board& board, Tetromino t, Rotation rotation);

}  // namespace tptps
