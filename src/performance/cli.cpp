#include "cli.hpp"

#include <cstdlib>

#include "CLI/App.hpp"
#include "fmt/chrono.h"
#include "fmt/core.h"

namespace tptps {

[[noreturn]] void show_usage_and_exit(const CLI::App& app, const char* error_message = nullptr, const std::optional<CLI::ParseError>& error = {})
{
    if (error_message)
        fmt::print(stderr, "\n{}\n", error_message);

    std::exit(error ? app.exit(error.value()) : 0);
}

CommandLine::CommandLine(std::span<const char*> args)
{
    const char* description = "TPTPS Performance";

    start_time_ = std::time(nullptr);

    CLI::App app{description};
    app.add_option("filename", filename_, "CSV output filename (without \".csv\")")->required();
    app.add_flag("-q,--quiet", quiet_, "suppress progress output");

    try {
        app.parse(static_cast<int>(args.size()), args.data());
    } catch (const CLI::ParseError& error) {
        show_usage_and_exit(app, nullptr, error);
    }

    // remove ".csv" extension from output filename
    std::filesystem::path out_filename{filename_};

    if (out_filename.extension() == ".csv") {
        out_filename.replace_extension("");
        filename_ = out_filename.string();
    }
}

std::string CommandLine::build_output_filename(const std::string& suffix) const
{
    return fmt::format("{}_{:%F_%H%M%S}_{}.csv", filename_, fmt::localtime(start_time_), suffix);
}

}  // namespace tptps
