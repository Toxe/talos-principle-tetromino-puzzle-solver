#pragma once

#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

namespace tptps {

template <typename T>
T mean(const std::vector<T>& values)
{
    assert(!values.empty());

    return std::accumulate(values.begin(), values.end(), T{}) / static_cast<T>(values.size());
}

template <typename T>
T median(std::vector<T> values)
{
    assert(!values.empty());

    if (values.size() % 2) {
        const auto m = values.begin() + values.size() / 2;
        std::nth_element(values.begin(), m, values.end());
        return *m;
    } else {
        const auto m = values.begin() + values.size() / 2 - 1;
        std::nth_element(values.begin(), m, values.end());
        return std::midpoint(*m, *std::min_element(m + 1, values.end()));
    }
}

}  // namespace tptps
