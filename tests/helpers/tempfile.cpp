#include "tempfile.hpp"

#include <random>

#include <filesystem>
#include <fstream>

namespace tptps {

std::string generate_tempfile_name()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(100000, 999999);

    const auto temp_dir_path = std::filesystem::temp_directory_path();
    std::string name;

    while (true) {
        auto tmp = temp_dir_path / ("tptps_tests_tmp_" + std::to_string(dist(gen)));

        if (!std::filesystem::exists(tmp)) {
            name = tmp.string();
            break;
        }
    }

    return name;
}

std::string read_tempfile_content(const std::string& filename)
{
    std::ifstream in{filename, std::ifstream::binary};
    return std::string{std::istreambuf_iterator<char>{in}, std::istreambuf_iterator<char>{}};
}

}  // namespace tptps
