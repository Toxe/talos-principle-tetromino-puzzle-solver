#include "catch2/catch_test_macros.hpp"

#include "../../src/lib/solver/rotation.hpp"

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

        CHECK(orientations_I.has(Rotation::r0));
        CHECK(orientations_I.has(Rotation::r90));
        CHECK(orientations_I.has(Rotation::r180) == false);
        CHECK(orientations_I.has(Rotation::r270) == false);

        CHECK(orientations_O.has(Rotation::r0));
        CHECK(orientations_O.has(Rotation::r90) == false);
        CHECK(orientations_O.has(Rotation::r180) == false);
        CHECK(orientations_O.has(Rotation::r270) == false);

        CHECK(orientations_T.has(Rotation::r0));
        CHECK(orientations_T.has(Rotation::r90));
        CHECK(orientations_T.has(Rotation::r180));
        CHECK(orientations_T.has(Rotation::r270));

        CHECK(orientations_J.has(Rotation::r0));
        CHECK(orientations_J.has(Rotation::r90));
        CHECK(orientations_J.has(Rotation::r180));
        CHECK(orientations_J.has(Rotation::r270));

        CHECK(orientations_L.has(Rotation::r0));
        CHECK(orientations_L.has(Rotation::r90));
        CHECK(orientations_L.has(Rotation::r180));
        CHECK(orientations_L.has(Rotation::r270));

        CHECK(orientations_S.has(Rotation::r0));
        CHECK(orientations_S.has(Rotation::r90));
        CHECK(orientations_S.has(Rotation::r180) == false);
        CHECK(orientations_S.has(Rotation::r270) == false);

        CHECK(orientations_Z.has(Rotation::r0));
        CHECK(orientations_Z.has(Rotation::r90));
        CHECK(orientations_Z.has(Rotation::r180) == false);
        CHECK(orientations_Z.has(Rotation::r270) == false);
    }
}

}  // namespace tptps
