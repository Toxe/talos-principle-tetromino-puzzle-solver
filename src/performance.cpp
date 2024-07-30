#include <cstdlib>
#include <string_view>

#include "fmt/core.h"

#include "solver/solver.hpp"

using namespace tptps;

[[noreturn]] void die(const std::string_view msg)
{
    fmt::print("{}\n", msg);
    std::exit(1);
}

void run(const std::string_view section, const std::string_view name, const Square size, const std::vector<Tetromino>& tetrominoes)
{
    fmt::print("{:>11} | {:>16} | ", section, name);

    SolverStats stats;
    const auto solution = solve_puzzle(Board{size.x, size.y}, tetrominoes, stats);

    if (!solution || !solution->is_finished())
        die("error, no solution found");

    fmt::print("{}\n", stats.print());
}

int main()
{
    fmt::print("{:>11} | {:>16} | {:>12} | {:>19} | {:>12}\n", "Section", "Name", "Checks", "Possible Placements", "Time");
    fmt::print("------------+------------------+--------------+---------------------+-------------\n");

    run("World Hub A", "Tutorial Puzzle", {4, 3}, {Tetromino::J, Tetromino::J, Tetromino::Z});
    run("World Hub A", "Gate A", {4, 4}, {Tetromino::I, Tetromino::Z, Tetromino::J, Tetromino::L});
    run("World Hub A", "Laser Connector", {4, 3}, {Tetromino::L, Tetromino::T, Tetromino::T});
    run("World Hub A", "Cube", {4, 4}, {Tetromino::L, Tetromino::T, Tetromino::T, Tetromino::Z});
    run("World Hub A", "Star Gate A", {8, 5}, {Tetromino::L, Tetromino::J, Tetromino::Z, Tetromino::Z, Tetromino::S, Tetromino::S, Tetromino::T, Tetromino::T, Tetromino::T, Tetromino::T});
    run("World Hub B", "Gate B", {4, 5}, {Tetromino::I, Tetromino::T, Tetromino::T, Tetromino::L, Tetromino::Z});
    run("World Hub B", "Fan", {4, 5}, {Tetromino::T, Tetromino::T, Tetromino::L, Tetromino::S, Tetromino::Z});
    run("World Hub B", "Recording", {4, 5}, {Tetromino::S, Tetromino::Z, Tetromino::J, Tetromino::T, Tetromino::T});
    run("World Hub B", "Laser Connector", {7, 4}, {Tetromino::I, Tetromino::I, Tetromino::S, Tetromino::Z, Tetromino::L, Tetromino::T, Tetromino::T});
    run("World Hub B", "Star Gate B", {8, 5}, {Tetromino::I, Tetromino::I, Tetromino::O, Tetromino::T, Tetromino::T, Tetromino::T, Tetromino::T, Tetromino::J, Tetromino::L, Tetromino::L});
    run("World Hub C", "Gate C", {4, 6}, {Tetromino::L, Tetromino::J, Tetromino::J, Tetromino::T, Tetromino::T, Tetromino::Z});
    run("World Hub C", "Platform", {4, 6}, {Tetromino::O, Tetromino::I, Tetromino::Z, Tetromino::L, Tetromino::T, Tetromino::T});
    run("World Hub C", "Blue Laser", {7, 4}, {Tetromino::I, Tetromino::Z, Tetromino::Z, Tetromino::T, Tetromino::T, Tetromino::L, Tetromino::J});
    run("World Hub C", "Messenger Tomb", {6, 6}, {Tetromino::O, Tetromino::O, Tetromino::L, Tetromino::L, Tetromino::J, Tetromino::J, Tetromino::I, Tetromino::Z, Tetromino::Z});
}
