#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include <array>

#include "../../src/performance/cli.hpp"

namespace tptps {

TEST_CASE("performance/cli")
{
    SECTION("output CSV filenames")
    {
        auto args = std::to_array({"performance", "output"});
        const CommandLine cli(args);

        CHECK_THAT(cli.measurements_filename(), Catch::Matchers::Matches(R"(output_\d{4}-\d{2}-\d{2}_\d{6}_measurements\.csv)"));
        CHECK_THAT(cli.summary_filename(), Catch::Matchers::Matches(R"(output_\d{4}-\d{2}-\d{2}_\d{6}_summary\.csv)"));
    }

    SECTION("quiet")
    {
        SECTION("disabled (default)")
        {
            auto args = std::to_array({"performance", "output"});
            const CommandLine cli(args);

            CHECK(cli.quiet() == false);
        }

        SECTION("enabled")
        {
            auto args1 = std::to_array({"performance", "output", "-q"});
            auto args2 = std::to_array({"performance", "output", "--quiet"});
            const CommandLine cli1(args1);
            const CommandLine cli2(args2);

            CHECK(cli1.quiet());
            CHECK(cli2.quiet());
        }
    }
}

}  // namespace tptps
