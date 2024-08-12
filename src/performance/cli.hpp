#pragma once

#include <ctime>
#include <span>
#include <string>

namespace tptps {

class CommandLine {
public:
    explicit CommandLine(std::span<const char*> args);

    [[nodiscard]] std::string measurements_filename() const { return build_output_filename("measurements"); }
    [[nodiscard]] std::string summary_filename() const { return build_output_filename("summary"); }
    [[nodiscard]] bool quiet() const { return quiet_; }

private:
    std::time_t start_time_;
    std::string filename_;
    bool quiet_ = false;

    std::string build_output_filename(const std::string& suffix) const;
};

}  // namespace tptps
