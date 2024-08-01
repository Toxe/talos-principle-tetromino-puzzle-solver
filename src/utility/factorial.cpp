#include "factorial.hpp"

namespace tptps {

uint64_t factorial(int n)
{
    if (n <= 1)
        return 1;

    uint64_t fac = 1;

    for (int i = 1; i <= n; ++i)
        fac *= static_cast<uint64_t>(i);

    return fac;
}

}  // namespace tptps
