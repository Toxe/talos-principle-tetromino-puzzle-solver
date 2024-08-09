#pragma once

#include <chrono>
#include <optional>
#include <vector>

#include "board.hpp"
#include "placement.hpp"
#include "rotation.hpp"
#include "solver_status.hpp"
#include "tetrominoes.hpp"

namespace tptps {

std::optional<Board> solve_puzzle(Board& board, std::vector<Tetromino> tetrominoes, SolverStatus& status);
std::vector<Placement> find_all_possible_placements(const Board& board, Tetromino t);
std::vector<Placement> find_possible_placements_for_rotation(const Board& board, Tetromino t, Rotation rotation);

}  // namespace tptps
