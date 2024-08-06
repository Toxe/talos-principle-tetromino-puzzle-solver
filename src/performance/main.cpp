#include <algorithm>
#include <array>
#include <chrono>
#include <cstdlib>
#include <string>
#include <string_view>
#include <tuple>

#include "fmt/core.h"

#include "cli.hpp"
#include "csv.hpp"
#include "solver/solver.hpp"
#include "utility/duration.hpp"
#include "utility/factorial.hpp"
#include "utility/statistics.hpp"

using namespace std::literals::chrono_literals;
using namespace tptps;

[[noreturn]] void die(const std::string_view msg)
{
    fmt::print(stderr, "error, {}\n", msg);
    std::exit(1);
}

std::string dump_tetrominoes(const std::vector<Tetromino>& tetrominoes)
{
    std::string s;

    for (const auto t : tetrominoes)
        s += static_cast<char>(t);

    return s;
}

std::string dump_csv_stats(const std::vector<uint64_t>& values)
{
    const auto mm = std::minmax_element(values.begin(), values.end());
    return fmt::format("{},{},{},{}", *mm.first, *mm.second, mean(values), median(values));
}

std::string dump_csv_stats(const std::vector<std::chrono::nanoseconds::rep>& values)
{
    const auto mm = std::minmax_element(values.begin(), values.end());
    return fmt::format("{},{},{},{}", print_duration(std::chrono::nanoseconds{*mm.first}), print_duration(std::chrono::nanoseconds{*mm.second}), print_duration(std::chrono::nanoseconds{mean(values)}), print_duration(std::chrono::nanoseconds{median(values)}));
}

uint64_t count_tetromino_permutations(std::vector<Tetromino> tetrominoes)
{
    uint64_t n = 0;

    std::sort(tetrominoes.begin(), tetrominoes.end());

    do {
        ++n;
    } while (std::next_permutation(tetrominoes.begin(), tetrominoes.end()));

    return n;
}

SolverStats solve(const Square size, const std::vector<Tetromino>& tetrominoes)
{
    SolverStats stats;
    Board board{size.x, size.y};

    const auto solution = solve_puzzle(board, tetrominoes, stats);

    if (!solution || !solution->is_filled())
        die(fmt::format("no solution found for: \"{}\"", dump_tetrominoes(tetrominoes)));

    return stats;
}

void run(CSVFile& csv_measurements, CSVFile& csv_summary, const std::string_view section, const std::string_view name, const Square size, std::vector<Tetromino> tetrominoes)
{
    const uint64_t max_runs = count_tetromino_permutations(tetrominoes);
    uint64_t run_count = 0;

    std::vector<std::chrono::nanoseconds::rep> durations;
    std::vector<uint64_t> placements_checked;
    std::vector<uint64_t> possible_placements_calculated;

    std::sort(tetrominoes.begin(), tetrominoes.end());

    const auto total_time_begin = std::chrono::steady_clock::now();

    do {
        const auto t0 = std::chrono::steady_clock::now();
        const auto stats = solve(size, tetrominoes);
        const auto t1 = std::chrono::steady_clock::now();
        const auto dur = t1 - t0;

        ++run_count;

        durations.push_back(dur.count());
        placements_checked.push_back(stats.placements_checked);
        possible_placements_calculated.push_back(stats.possible_placements_calculated);

        csv_measurements.write(section, name, print_square(size), run_count, max_runs, dump_tetrominoes(tetrominoes), print_duration(dur), stats.placements_checked, stats.possible_placements_calculated);

        if (std::chrono::steady_clock::now() - total_time_begin >= 10s)
            break;
    } while (std::next_permutation(tetrominoes.begin(), tetrominoes.end()));

    const auto total_time_end = std::chrono::steady_clock::now();

    csv_summary.write(section, name, print_square(size), run_count, max_runs, print_duration(total_time_end - total_time_begin), dump_csv_stats(durations), dump_csv_stats(placements_checked), dump_csv_stats(possible_placements_calculated));
}

int main(int argc, const char* argv[])
{
    const CommandLine cli({argv, static_cast<std::size_t>(argc)});

    CSVFile csv_measurements{cli.measurements_filename()};
    CSVFile csv_summary{cli.summary_filename()};

    csv_measurements.write(
        "Section",
        "Name",
        "Size",
        "Run Count",
        "Max Runs",
        "Tetrominoes",
        "Duration",
        "Placements Checked",
        "Placements Calculated");

    csv_summary.write(
        "Section",
        "Name",
        "Size",
        "Run Count",
        "Max Runs",
        "Total Duration",
        "Duration (min)",
        "Duration (max)",
        "Duration (mean)",
        "Duration (median)",
        "Placements Checked (min)",
        "Placements Checked (max)",
        "Placements Checked (mean)",
        "Placements Checked (median)",
        "Placements Calculated (min)",
        "Placements Calculated (max)",
        "Placements Calculated (mean)",
        "Placements Calculated (median)");

    run(csv_measurements, csv_summary, "World Hub A", "Tutorial Puzzle", {4, 3}, {Tetromino::J, Tetromino::J, Tetromino::Z});
    run(csv_measurements, csv_summary, "World Hub A", "Gate A", {4, 4}, {Tetromino::I, Tetromino::Z, Tetromino::J, Tetromino::L});
    run(csv_measurements, csv_summary, "World Hub A", "Laser Connector", {4, 3}, {Tetromino::L, Tetromino::T, Tetromino::T});
    run(csv_measurements, csv_summary, "World Hub A", "Cube", {4, 4}, {Tetromino::L, Tetromino::T, Tetromino::T, Tetromino::Z});
    run(csv_measurements, csv_summary, "World Hub B", "Gate B", {4, 5}, {Tetromino::I, Tetromino::T, Tetromino::T, Tetromino::L, Tetromino::Z});
    run(csv_measurements, csv_summary, "World Hub B", "Fan", {4, 5}, {Tetromino::T, Tetromino::T, Tetromino::L, Tetromino::S, Tetromino::Z});
    run(csv_measurements, csv_summary, "World Hub B", "Recording", {4, 5}, {Tetromino::S, Tetromino::Z, Tetromino::J, Tetromino::T, Tetromino::T});
    run(csv_measurements, csv_summary, "World Hub C", "Gate C", {4, 6}, {Tetromino::L, Tetromino::J, Tetromino::J, Tetromino::T, Tetromino::T, Tetromino::Z});
    run(csv_measurements, csv_summary, "World Hub C", "Platform", {4, 6}, {Tetromino::O, Tetromino::I, Tetromino::Z, Tetromino::L, Tetromino::T, Tetromino::T});
    // run(csv_measurements, csv_summary, "Messenger Island A", "Cube", {6, 6}, {Tetromino::L, Tetromino::L, Tetromino::J, Tetromino::T, Tetromino::T, Tetromino::O, Tetromino::O, Tetromino::I, Tetromino::S});  // long
    run(csv_measurements, csv_summary, "Messenger Island A", "Messenger Tomb", {4, 5}, {Tetromino::I, Tetromino::O, Tetromino::O, Tetromino::J, Tetromino::J});
    // run(csv_measurements, csv_summary, "Messenger Island B", "Laser Connector 1", {4, 10}, {Tetromino::T, Tetromino::T, Tetromino::T, Tetromino::T, Tetromino::Z, Tetromino::Z, Tetromino::S, Tetromino::J, Tetromino::I, Tetromino::I});  // long
    run(csv_measurements, csv_summary, "Messenger Island B", "Laser Connector 2", {7, 4}, {Tetromino::I, Tetromino::I, Tetromino::S, Tetromino::Z, Tetromino::L, Tetromino::T, Tetromino::T});
    run(csv_measurements, csv_summary, "Messenger Island C", "Blue Laser", {7, 4}, {Tetromino::I, Tetromino::Z, Tetromino::Z, Tetromino::T, Tetromino::T, Tetromino::L, Tetromino::J});
    // run(csv_measurements, csv_summary, "Messenger Island C", "Messenger Tomb", {6, 6}, {Tetromino::O, Tetromino::O, Tetromino::L, Tetromino::L, Tetromino::J, Tetromino::J, Tetromino::I, Tetromino::Z, Tetromino::Z});
    // run(csv_measurements, csv_summary, "World Hub A", "Star Gate A", {8, 5}, {Tetromino::L, Tetromino::J, Tetromino::Z, Tetromino::Z, Tetromino::S, Tetromino::S, Tetromino::T, Tetromino::T, Tetromino::T, Tetromino::T});
    // run(csv_measurements, csv_summary, "World Hub B", "Star Gate B", {8, 5}, {Tetromino::I, Tetromino::I, Tetromino::O, Tetromino::T, Tetromino::T, Tetromino::T, Tetromino::T, Tetromino::J, Tetromino::L, Tetromino::L});
}
