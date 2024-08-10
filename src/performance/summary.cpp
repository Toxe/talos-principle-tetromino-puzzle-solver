#include "summary.hpp"

#include <algorithm>
#include <numeric>

#include "fmt/color.h"
#include "fmt/core.h"

#include "utility/duration.hpp"
#include "utility/statistics.hpp"
#include "utility/str.hpp"

namespace tptps {

void print_row(const std::vector<std::vector<std::string>>& rows, const std::size_t row, const std::vector<int>& column_sizes)
{
    const auto values = rows[row];

    for (std::size_t i = 0; i < values.size(); ++i) {
        const std::string format = fmt::format("{{:>{}}}", column_sizes[i]);
        const std::string s = fmt::format(fmt::runtime(format), values[i]);

        if (i > 0)
            fmt::print(" │ ");

        if (row == 0)
            fmt::print(fmt::emphasis::bold, s);  // header
        else if (row > 0 && i == 4)
            fmt::print(fg(fmt::color::cornflower_blue), s);  // median
        else
            fmt::print("{}", s);
    }

    fmt::print("\n");
}

void print_header(const std::vector<std::vector<std::string>>& rows, const std::vector<int>& column_sizes)
{
    print_row(rows, 0, column_sizes);

    const auto values = rows[0];

    for (std::size_t i = 0; i < values.size(); ++i) {
        const std::string format = fmt::format("{{:─>{}}}", column_sizes[i]);

        if (i > 0)
            fmt::print("─┼─");

        fmt::print(fmt::runtime(format), "");
    }

    fmt::print("\n");
}

int column_width(const std::vector<std::vector<std::string>>& rows, const std::size_t col)
{
    int width = 0;

    for (const auto& row : rows)
        width = std::max(width, str_mb_length(row[col]));

    return width;
}

std::vector<int> calc_column_sizes(const std::vector<std::vector<std::string>>& rows)
{
    std::vector<int> column_sizes;

    for (std::size_t i = 0; i < rows[0].size(); ++i)
        column_sizes.push_back(column_width(rows, i));

    return column_sizes;
}

void print_summary(const std::chrono::nanoseconds total_duration, const std::vector<uint64_t>& durations, const std::vector<uint64_t>& function_called, const std::vector<uint64_t>& placements_calculated)
{
    const auto mm_dur = std::minmax_element(durations.begin(), durations.end());
    const auto mm_func = std::minmax_element(function_called.begin(), function_called.end());
    const auto mm_calc = std::minmax_element(placements_calculated.begin(), placements_calculated.end());

    std::vector<std::vector<std::string>> rows;

    rows.push_back({"", "min", "max", "mean", "median", "total"});

    rows.push_back({
        "Duration",
        print_duration(std::chrono::nanoseconds{*mm_dur.first}),
        print_duration(std::chrono::nanoseconds{*mm_dur.second}),
        print_duration(std::chrono::nanoseconds{mean(durations)}),
        print_duration(std::chrono::nanoseconds{median(durations)}),
        print_duration(total_duration),
    });

    rows.push_back({
        "Function Called",
        std::to_string(*mm_func.first),
        std::to_string(*mm_func.second),
        std::to_string(mean(function_called)),
        std::to_string(median(function_called)),
        "",
    });

    rows.push_back({
        "Placements Calculated",
        std::to_string(*mm_calc.first),
        std::to_string(*mm_calc.second),
        std::to_string(mean(placements_calculated)),
        std::to_string(median(placements_calculated)),
        "",
    });

    const auto column_sizes = calc_column_sizes(rows);

    print_header(rows, column_sizes);

    for (std::size_t i = 1; i < rows.size(); ++i)
        print_row(rows, i, column_sizes);
}

}  // namespace tptps
