#include <algorithm>
#include <array>
#include <chrono>
#include <cstdlib>
#include <locale>
#include <string>
#include <string_view>
#include <tuple>

#include "fmt/core.h"

#include "cli.hpp"
#include "csv.hpp"
#include "solver/solver.hpp"
#include "summary.hpp"
#include "utility/duration.hpp"
#include "utility/factorial.hpp"
#include "utility/statistics.hpp"
#include "utility/str.hpp"

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

uint64_t count_tetromino_permutations(std::vector<Tetromino> tetrominoes)
{
    uint64_t n = 0;

    std::sort(tetrominoes.begin(), tetrominoes.end());

    do {
        ++n;
    } while (std::next_permutation(tetrominoes.begin(), tetrominoes.end()));

    return n;
}

std::chrono::nanoseconds calc_total_duration(const std::vector<uint64_t>& durations)
{
    return std::chrono::nanoseconds{std::accumulate(durations.begin(), durations.end(), uint64_t{0})};
}

void print_header(const std::string_view section, const std::string_view name, const Square size, const uint64_t max_runs, const std::vector<Tetromino>& tetrominoes)
{
    const auto header = fmt::format("{}, {}: {}, {}, {} permutations", section, name, print_square(size), dump_tetrominoes(tetrominoes), max_runs);

    fmt::print("{}\n", header);
    fmt::print("{}\n", std::string(str_mb_length(header), '='));
}

void run(CSVFile& csv_measurements, CSVFile& csv_summary, const std::string_view section, const std::string_view name, const Square size, std::vector<Tetromino> tetrominoes)
{
    const uint64_t max_runs = count_tetromino_permutations(tetrominoes);
    uint64_t run_count = 0;

    std::vector<uint64_t> durations;
    std::vector<uint64_t> function_called;
    std::vector<uint64_t> placements_calculated;

    std::sort(tetrominoes.begin(), tetrominoes.end());

    print_header(section, name, size, max_runs, tetrominoes);

    const auto time_begin = std::chrono::steady_clock::now();

    do {
        ++run_count;

        SolverStatus status{fmt::format("[{}/{} | {}]", run_count, max_runs, dump_tetrominoes(tetrominoes))};
        Board board{size.x, size.y};

        const auto solution = solve_puzzle(board, tetrominoes, status);

        if (!solution || !solution->is_filled())
            die(fmt::format("no solution found for: \"{}\"", dump_tetrominoes(tetrominoes)));

        status.print_log_message("\n");

        durations.push_back(status.duration().count());
        function_called.push_back(status.function_called());
        placements_calculated.push_back(status.placements_calculated());

        csv_measurements.write(section, name, print_square(size), run_count, max_runs, dump_tetrominoes(tetrominoes), status.duration().count(), status.function_called(), status.placements_calculated());

        if (std::chrono::steady_clock::now() - time_begin >= 30s)
            break;
    } while (std::next_permutation(tetrominoes.begin(), tetrominoes.end()));

    const auto total_duration = calc_total_duration(durations);

    fmt::print("\n");
    print_summary(total_duration, durations, function_called, placements_calculated);
    fmt::print("\n\n\n");

    csv_summary.write(section, name, print_square(size), run_count, max_runs, total_duration.count(), dump_csv_stats(durations), dump_csv_stats(function_called), dump_csv_stats(placements_calculated));
}

int main(int argc, const char* argv[])
{
    std::setlocale(LC_ALL, "en_US.utf8");

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
        "Function Called",
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
        "Function Called (min)",
        "Function Called (max)",
        "Function Called (mean)",
        "Function Called (median)",
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
