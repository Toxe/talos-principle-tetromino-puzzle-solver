#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_all.hpp"

#include "../src/solver/rotation.hpp"

namespace tptps {

TEST_CASE("solver/rotation")
{
    SECTION("list all distinct tetromino rotations")
    {
        const auto orientations_I = get_distinct_tetromino_rotations(Tetromino::I);
        const auto orientations_O = get_distinct_tetromino_rotations(Tetromino::O);
        const auto orientations_T = get_distinct_tetromino_rotations(Tetromino::T);
        const auto orientations_J = get_distinct_tetromino_rotations(Tetromino::J);
        const auto orientations_L = get_distinct_tetromino_rotations(Tetromino::L);
        const auto orientations_S = get_distinct_tetromino_rotations(Tetromino::S);
        const auto orientations_Z = get_distinct_tetromino_rotations(Tetromino::Z);

        CHECK_THAT(orientations_I, Catch::Matchers::SizeIs(2));
        CHECK_THAT(orientations_O, Catch::Matchers::SizeIs(1));
        CHECK_THAT(orientations_T, Catch::Matchers::SizeIs(4));
        CHECK_THAT(orientations_J, Catch::Matchers::SizeIs(4));
        CHECK_THAT(orientations_L, Catch::Matchers::SizeIs(4));
        CHECK_THAT(orientations_S, Catch::Matchers::SizeIs(2));
        CHECK_THAT(orientations_Z, Catch::Matchers::SizeIs(2));

        CHECK_THAT(orientations_I, Catch::Matchers::UnorderedRangeEquals(std::vector<Rotation>{Rotation::r0, Rotation::r90}));
        CHECK_THAT(orientations_O, Catch::Matchers::UnorderedRangeEquals(std::vector<Rotation>{Rotation::r0}));
        CHECK_THAT(orientations_T, Catch::Matchers::UnorderedRangeEquals(std::vector<Rotation>{Rotation::r0, Rotation::r90, Rotation::r180, Rotation::r270}));
        CHECK_THAT(orientations_J, Catch::Matchers::UnorderedRangeEquals(std::vector<Rotation>{Rotation::r0, Rotation::r90, Rotation::r180, Rotation::r270}));
        CHECK_THAT(orientations_L, Catch::Matchers::UnorderedRangeEquals(std::vector<Rotation>{Rotation::r0, Rotation::r90, Rotation::r180, Rotation::r270}));
        CHECK_THAT(orientations_S, Catch::Matchers::UnorderedRangeEquals(std::vector<Rotation>{Rotation::r0, Rotation::r90}));
        CHECK_THAT(orientations_Z, Catch::Matchers::UnorderedRangeEquals(std::vector<Rotation>{Rotation::r0, Rotation::r90}));
    }
}

}  // namespace tptps
