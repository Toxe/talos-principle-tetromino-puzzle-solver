#include <filesystem>

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "../../src/performance/csv.hpp"
#include "../helpers/tempfile.hpp"

namespace tptps {

TEST_CASE("performance/csv")
{
    SECTION("creates CSV file with content")
    {
        const auto filename = generate_tempfile_name();

        {
            CSVFile csv{filename};
            csv.write("Column A", "Column B", "Column C");
            csv.write("one");
            csv.write("two", "values");
            csv.write("AAA", "BBB", "CCC");
            csv.write(999);
        }

        REQUIRE(std::filesystem::exists(filename));

        const std::string s = "Column A,Column B,Column C\n"
                              "one\n"
                              "two,values\n"
                              "AAA,BBB,CCC\n"
                              "999\n";

        CHECK_THAT(read_tempfile_content(filename), Catch::Matchers::Equals(s));

        std::filesystem::remove(filename);
        CHECK(std::filesystem::exists(filename) == false);
    }
}

}  // namespace tptps
