#include "catch2/catch_test_macros.hpp"

#include "../src/utility/factorial.hpp"

namespace tptps {

TEST_CASE("utility/factorial")
{
    SECTION("calculate factorials")
    {
        CHECK(factorial(0) == 1);
        CHECK(factorial(1) == 1);
        CHECK(factorial(2) == 2);
        CHECK(factorial(3) == 6);
        CHECK(factorial(4) == 24);
        CHECK(factorial(5) == 120);
        CHECK(factorial(6) == 720);
        CHECK(factorial(7) == 5040);
        CHECK(factorial(8) == 40320);
        CHECK(factorial(9) == 362880);
        CHECK(factorial(10) == 3628800);
        CHECK(factorial(11) == 39916800);
        CHECK(factorial(12) == 479001600);
        CHECK(factorial(13) == 6227020800);
        CHECK(factorial(14) == 87178291200);
        CHECK(factorial(15) == 1307674368000);
        CHECK(factorial(16) == 20922789888000);
        CHECK(factorial(17) == 355687428096000);
        CHECK(factorial(18) == 6402373705728000);
        CHECK(factorial(19) == 121645100408832000);
        CHECK(factorial(20) == 2432902008176640000);
    }
}

}  // namespace tptps
