#include "fmt/core.h"

#include "solver/solver.hpp"

using namespace tptps;

int main()
{
    SolverStats stats;
    const auto solution = solve_puzzle(Board{4, 6}, {{Tetromino::L, Tetromino::J, Tetromino::J, Tetromino::T, Tetromino::T, Tetromino::Z}}, stats);

    if (!solution) {
        fmt::print("no solution found\n");
        return 1;
    }

    fmt::print("{}\n", solution->print());
    fmt::print("{}\n", stats.print());
}
