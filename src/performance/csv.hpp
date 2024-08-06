#pragma once

#include <cassert>
#include <fstream>
#include <string>

namespace tptps {

class CSVFile {
public:
    CSVFile(const std::string& filename) : out_{filename, std::ofstream::binary} { }

    template <typename T, typename... Types>
    void write(T arg, Types... args)
    {
        assert(out_.is_open());

        if constexpr (sizeof...(args) > 0) {
            out_ << arg << ',';
            write(args...);
        }

        if constexpr (sizeof...(args) == 0)
            out_ << arg << '\n';
    }

private:
    std::ofstream out_;
};

}  // namespace tptps
