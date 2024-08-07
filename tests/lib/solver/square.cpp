#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "../../src/lib/solver/square.hpp"

namespace tptps {

TEST_CASE("solver/square")
{
    SECTION("print Squares")
    {
        CHECK_THAT(print_square({2, 3}), Catch::Matchers::Equals("2×3"));
        CHECK_THAT(print_square({5, 4}), Catch::Matchers::Equals("5×4"));
        CHECK_THAT(print_square({10, 8}), Catch::Matchers::Equals("10×8"));
        CHECK_THAT(print_square({4, 12}), Catch::Matchers::Equals("4×12"));
    }
}

}  // namespace tptps
