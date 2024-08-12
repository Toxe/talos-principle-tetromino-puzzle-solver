#include "catch2/catch_test_macros.hpp"

#include "../../src/lib/solver/placement_mask.hpp"

namespace tptps {

TEST_CASE("solver/placement_mask")
{
    SECTION("can set and test mask bits")
    {
        PlacementMask mask{3, 2};

        CHECK(mask.width() == 3);
        CHECK(mask.height() == 2);

        CHECK(mask.at({0, 0}) == false);
        CHECK(mask.at({1, 0}) == false);
        CHECK(mask.at({2, 0}) == false);
        CHECK(mask.at({0, 1}) == false);
        CHECK(mask.at({1, 1}) == false);
        CHECK(mask.at({2, 1}) == false);

        mask.set({0, 0});
        mask.set({1, 0});
        mask.set({2, 0});
        mask.set({1, 1});

        CHECK(mask.at({0, 0}));
        CHECK(mask.at({1, 0}));
        CHECK(mask.at({2, 0}));
        CHECK(mask.at({0, 1}) == false);
        CHECK(mask.at({1, 1}));
        CHECK(mask.at({2, 1}) == false);
    }

    SECTION("create a placement mask from a string")
    {
        SECTION("L")
        {
            const auto mask = placement_mask_from_string({
                "#.",
                "#.",
                "##",
            });

            CHECK(mask.width() == 2);
            CHECK(mask.height() == 3);

            CHECK(mask.at({0, 0}));
            CHECK(mask.at({1, 0}) == false);
            CHECK(mask.at({0, 1}));
            CHECK(mask.at({1, 1}) == false);
            CHECK(mask.at({0, 2}));
            CHECK(mask.at({1, 2}));
        }

        SECTION("I")
        {
            const auto mask = placement_mask_from_string({
                "####",
            });

            CHECK(mask.width() == 4);
            CHECK(mask.height() == 1);

            CHECK(mask.at({0, 0}));
            CHECK(mask.at({1, 0}));
            CHECK(mask.at({2, 0}));
            CHECK(mask.at({3, 0}));
        }

        SECTION("T")
        {
            const auto mask = placement_mask_from_string({
                ".#.",
                "###",
            });

            CHECK(mask.width() == 3);
            CHECK(mask.height() == 2);

            CHECK(mask.at({0, 0}) == false);
            CHECK(mask.at({1, 0}));
            CHECK(mask.at({2, 0}) == false);
            CHECK(mask.at({0, 1}));
            CHECK(mask.at({1, 1}));
            CHECK(mask.at({2, 1}));
        }
    }

    SECTION("get placement mask for rotated tetromino")
    {
        SECTION("L, no rotation")
        {
            const auto mask = placement_mask_from_string({
                "#.",
                "#.",
                "##",
            });

            CHECK(get_tetromino_placement_mask(Tetromino::L, Rotation::r0) == mask);
        }

        SECTION("L, rotated three times")
        {
            const auto mask = placement_mask_from_string({
                "..#",
                "###",
            });

            CHECK(get_tetromino_placement_mask(Tetromino::L, Rotation::r270) == mask);
        }

        SECTION("I, no rotation")
        {
            const auto mask = placement_mask_from_string({
                "####",
            });

            CHECK(get_tetromino_placement_mask(Tetromino::I, Rotation::r0) == mask);
        }

        SECTION("I, rotated once")
        {
            const auto mask = placement_mask_from_string({
                "#",
                "#",
                "#",
                "#",
            });

            CHECK(get_tetromino_placement_mask(Tetromino::I, Rotation::r90) == mask);
        }

        SECTION("O, rotated twice")
        {
            const auto mask = placement_mask_from_string({
                "##",
                "##",
            });

            CHECK(get_tetromino_placement_mask(Tetromino::O, Rotation::r180) == mask);
        }
    }
}

}  // namespace tptps
