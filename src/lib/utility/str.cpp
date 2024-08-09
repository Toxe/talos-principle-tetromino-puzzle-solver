#include "str.hpp"

#include <algorithm>
#include <cassert>
#include <cwchar>
#include <locale>
#include <stdexcept>

namespace tptps {

std::string str_tolower(const std::string& s)
{
    std::string dst{s};
    std::transform(dst.begin(), dst.end(), dst.begin(), [](const unsigned char c) { return static_cast<unsigned char>(std::tolower(c)); });
    return dst;
}

std::string str_tolower(const char* s)
{
    assert(s != nullptr);
    return str_tolower(std::string{s});
}

int str_mb_length(const std::string& s)
{
    assert(str_tolower(std::setlocale(LC_ALL, nullptr)) == "en_us.utf8");  // call std::setlocale(LC_ALL, "en_US.utf8") somewhere before running this

    const char* end = s.data() + s.size();
    std::mbstate_t mbs{};
    int length = 0;

    for (const char* ptr = s.data(); ptr != end; ++length) {
        const std::size_t n = std::mbrtowc(nullptr, ptr, end - ptr, &mbs);

        if (n >= 1 && n <= static_cast<std::size_t>(end - ptr)) {
            ptr += n;
        } else {
            // n <= 0
            throw std::runtime_error{"invalid code point"};
        }
    }

    return length;
}

}  // namespace tptps
