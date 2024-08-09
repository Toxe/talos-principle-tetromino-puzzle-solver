#include <chrono>

#include "fmt/core.h"

#include "solver/solver.hpp"
#include "utility/duration.hpp"

using namespace tptps;

int main()
{
    SolverStatus status;
    Board board{4, 6};

    const auto t0 = std::chrono::steady_clock::now();
    const auto solution = solve_puzzle(board, {{Tetromino::L, Tetromino::J, Tetromino::J, Tetromino::T, Tetromino::T, Tetromino::Z}}, status);
    const auto t1 = std::chrono::steady_clock::now();

    if (!solution) {
        fmt::print("no solution found\n");
        return 1;
    }

    fmt::print("{}\n", solution->print());
    fmt::print("{}\n", print_duration(t1 - t0));
}
