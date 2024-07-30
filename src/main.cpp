#include "fmt/core.h"

#include "solver/solver.hpp"

using namespace tptps;

int main()
{
    const auto solution = solve_puzzle(Board{4, 6}, {{Tetromino::L, Tetromino::J, Tetromino::J, Tetromino::T, Tetromino::T, Tetromino::Z}});

    if (!solution) {
        fmt::print("no solution found\n");
        return 1;
    }

    fmt::print("{}", solution->print());
}
