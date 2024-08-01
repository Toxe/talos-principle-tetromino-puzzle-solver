#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "../src/utility/duration.hpp"

using namespace std::literals::chrono_literals;

namespace tptps {

TEST_CASE("utility/duration")
{
    SECTION("print durations")
    {
        CHECK_THAT(print_duration(0ns), Catch::Matchers::Equals("0.000 ns"));
        CHECK_THAT(print_duration(250ns), Catch::Matchers::Equals("250.000 ns"));
        CHECK_THAT(print_duration(735ns), Catch::Matchers::Equals("735.000 ns"));

        CHECK_THAT(print_duration(1'000ns), Catch::Matchers::Equals("1.000 μs"));
        CHECK_THAT(print_duration(1'250ns), Catch::Matchers::Equals("1.250 μs"));
        CHECK_THAT(print_duration(1'735ns), Catch::Matchers::Equals("1.735 μs"));
        CHECK_THAT(print_duration(250'000ns), Catch::Matchers::Equals("250.000 μs"));
        CHECK_THAT(print_duration(735'000ns), Catch::Matchers::Equals("735.000 μs"));

        CHECK_THAT(print_duration(1'000'000ns), Catch::Matchers::Equals("1.000 ms"));
        CHECK_THAT(print_duration(1'250'000ns), Catch::Matchers::Equals("1.250 ms"));
        CHECK_THAT(print_duration(1'735'000ns), Catch::Matchers::Equals("1.735 ms"));
        CHECK_THAT(print_duration(250'000'000ns), Catch::Matchers::Equals("250.000 ms"));
        CHECK_THAT(print_duration(735'000'000ns), Catch::Matchers::Equals("735.000 ms"));

        CHECK_THAT(print_duration(1'000'000'000ns), Catch::Matchers::Equals("1.000 s"));
        CHECK_THAT(print_duration(1'250'000'000ns), Catch::Matchers::Equals("1.250 s"));
        CHECK_THAT(print_duration(1'735'000'000ns), Catch::Matchers::Equals("1.735 s"));
        CHECK_THAT(print_duration(250'000'000'000ns), Catch::Matchers::Equals("250.000 s"));
        CHECK_THAT(print_duration(735'000'000'000ns), Catch::Matchers::Equals("735.000 s"));

        CHECK_THAT(print_duration(1'000'000'000'000ns), Catch::Matchers::Equals("1000.000 s"));
        CHECK_THAT(print_duration(1'250'000'000'000ns), Catch::Matchers::Equals("1250.000 s"));
        CHECK_THAT(print_duration(1'735'000'000'000ns), Catch::Matchers::Equals("1735.000 s"));
    }
}

}  // namespace tptps
