#pragma once

#include <ctime>
#include <span>
#include <string>

namespace tptps {

class CommandLine {
public:
    explicit CommandLine(std::span<const char*> args);

    [[nodiscard]] const std::string measurements_filename() const { return build_output_filename("measurements"); }
    [[nodiscard]] const std::string summary_filename() const { return build_output_filename("summary"); }

private:
    std::time_t start_time_;
    std::string filename_;

    std::string build_output_filename(const std::string& suffix) const;
};

}  // namespace tptps
