#include <locale>

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "../../src/lib/utility/str.hpp"

using namespace std::string_literals;

namespace tptps {

TEST_CASE("utility/str")
{
    SECTION("str_tolower")
    {
        SECTION("std::string")
        {
            CHECK_THAT(str_tolower(""s), Catch::Matchers::Equals(""));
            CHECK_THAT(str_tolower("hello world"s), Catch::Matchers::Equals("hello world"));
            CHECK_THAT(str_tolower("HELLO WORLD"s), Catch::Matchers::Equals("hello world"));
            CHECK_THAT(str_tolower("987 @ 23!"s), Catch::Matchers::Equals("987 @ 23!"));
            CHECK_THAT(str_tolower("Mixed Case"s), Catch::Matchers::Equals("mixed case"));
        }

        SECTION("char*")
        {
            CHECK_THAT(str_tolower(""), Catch::Matchers::Equals(""));
            CHECK_THAT(str_tolower("hello world"), Catch::Matchers::Equals("hello world"));
            CHECK_THAT(str_tolower("HELLO WORLD"), Catch::Matchers::Equals("hello world"));
            CHECK_THAT(str_tolower("987 @ 23!"), Catch::Matchers::Equals("987 @ 23!"));
            CHECK_THAT(str_tolower("Mixed Case"), Catch::Matchers::Equals("mixed case"));
        }
    }

    SECTION("str_mb_length")
    {
        std::setlocale(LC_ALL, "en_US.utf8");

        CHECK(str_mb_length("") == 0);
        CHECK(str_mb_length("test") == 4);
        CHECK(str_mb_length("hello world") == 11);
        CHECK(str_mb_length("hello 🌍") == 7);
        CHECK(str_mb_length("4×3") == 3);
        CHECK(str_mb_length("12 μs") == 5);
        CHECK(str_mb_length("zß水🍌") == 4);
        CHECK(str_mb_length("♔♚") == 2);
        CHECK(str_mb_length("水") == 1);
        CHECK(str_mb_length("©℃→⅓∅∑") == 6);
        CHECK(str_mb_length("遍地开花") == 4);
        CHECK(str_mb_length("本文的目的") == 5);
        CHECK(str_mb_length("✅💡🐨🤔🎉🍕🚗") == 7);
        CHECK(str_mb_length("🆁🆇") == 2);

        // doesn't support glyphs that consist of more than one code point
        // CHECK(str_mb_length("🅿️") == 1);
        // CHECK(str_mb_length("🅰️") == 1);
        // CHECK(str_mb_length("❤️") == 1);
        // CHECK(str_mb_length("☢️") == 1);
    }
}

}  // namespace tptps
