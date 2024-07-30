#include <iostream>

#include "solver/solver.hpp"

using namespace tptps;

int main()
{
    const auto solution = solve_puzzle(Board{4, 6}, {{Tetromino::L, Tetromino::J, Tetromino::J, Tetromino::T, Tetromino::T, Tetromino::Z}});

    if (!solution) {
        std::cout << "no solution found";
        return 1;
    }

    std::cout << solution->print();
}
