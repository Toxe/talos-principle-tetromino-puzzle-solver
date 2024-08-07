#pragma once

#include <string>

namespace tptps {

std::string generate_tempfile_name();
std::string read_tempfile_content(const std::string& filename);

}  // namespace tptps
