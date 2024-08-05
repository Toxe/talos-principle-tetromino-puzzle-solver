#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "../src/solver/placement.hpp"

namespace tptps {

TEST_CASE("solver/placement")
{
    SECTION("can check and apply & revert placements")
    {
        Board board{4, 3};

        // check with empty Board
        CHECK(is_possible_placement(board, {{0, 0}, Tetromino::I, Rotation::r0}, get_tetromino_placement_mask(Tetromino::I, Rotation::r0)));
        CHECK(is_possible_placement(board, {{0, 0}, Tetromino::I, Rotation::r90}, get_tetromino_placement_mask(Tetromino::I, Rotation::r90)) == false);
        CHECK(is_possible_placement(board, {{2, 0}, Tetromino::L, Rotation::r0}, get_tetromino_placement_mask(Tetromino::L, Rotation::r0)));
        CHECK(is_possible_placement(board, {{3, 0}, Tetromino::L, Rotation::r0}, get_tetromino_placement_mask(Tetromino::L, Rotation::r0)) == false);
        CHECK(is_possible_placement(board, {{1, 0}, Tetromino::L, Rotation::r270}, get_tetromino_placement_mask(Tetromino::L, Rotation::r270)));
        CHECK(is_possible_placement(board, {{2, 0}, Tetromino::L, Rotation::r270}, get_tetromino_placement_mask(Tetromino::L, Rotation::r270)) == false);
        CHECK(is_possible_placement(board, {{3, 0}, Tetromino::L, Rotation::r270}, get_tetromino_placement_mask(Tetromino::L, Rotation::r270)) == false);
        CHECK(is_possible_placement(board, {{0, 0}, Tetromino::O, Rotation::r0}, get_tetromino_placement_mask(Tetromino::O, Rotation::r0)));

        // .L..
        // .L..
        // .LL.
        apply_placement(board, {{1, 0}, Tetromino::L, Rotation::r0});

        CHECK(board.at({1, 0}) == Tetromino::L);
        CHECK(board.at({1, 1}) == Tetromino::L);
        CHECK(board.at({1, 2}) == Tetromino::L);
        CHECK(board.at({2, 2}) == Tetromino::L);
        CHECK(board.is_empty_square({0, 0}));
        CHECK(board.is_empty_square({0, 1}));
        CHECK(board.is_empty_square({0, 2}));
        CHECK(board.is_empty_square({2, 0}));
        CHECK(board.is_empty_square({2, 1}));
        CHECK(board.is_empty_square({3, 0}));
        CHECK(board.is_empty_square({3, 1}));
        CHECK(board.is_empty_square({3, 2}));

        CHECK(is_possible_placement(board, {{2, 0}, Tetromino::T, Rotation::r90}, get_tetromino_placement_mask(Tetromino::T, Rotation::r90)));
        CHECK(is_possible_placement(board, {{2, 0}, Tetromino::T, Rotation::r270}, get_tetromino_placement_mask(Tetromino::T, Rotation::r270)) == false);

        // .L.T
        // .LTT
        // .LLT
        apply_placement(board, {{2, 0}, Tetromino::T, Rotation::r90});

        CHECK(board.at({3, 0}) == Tetromino::T);
        CHECK(board.at({2, 1}) == Tetromino::T);
        CHECK(board.at({3, 1}) == Tetromino::T);
        CHECK(board.at({3, 2}) == Tetromino::T);
        CHECK(board.is_empty_square({0, 0}));
        CHECK(board.is_empty_square({0, 1}));
        CHECK(board.is_empty_square({0, 2}));
        CHECK(board.is_empty_square({2, 0}));

        // check with mostly filled Board
        CHECK(is_possible_placement(board, {{0, 0}, Tetromino::I, Rotation::r90}, get_tetromino_placement_mask(Tetromino::I, Rotation::r90)) == false);
        CHECK(is_possible_placement(board, {{2, 0}, Tetromino::L, Rotation::r0}, get_tetromino_placement_mask(Tetromino::L, Rotation::r0)) == false);
        CHECK(is_possible_placement(board, {{1, 0}, Tetromino::L, Rotation::r270}, get_tetromino_placement_mask(Tetromino::L, Rotation::r270)) == false);
        CHECK(is_possible_placement(board, {{0, 0}, Tetromino::O, Rotation::r0}, get_tetromino_placement_mask(Tetromino::O, Rotation::r0)) == false);

        // revert placements
        revert_placement(board, {{2, 0}, Tetromino::T, Rotation::r90});
        CHECK(board.at({1, 0}) == Tetromino::L);
        CHECK(board.at({1, 1}) == Tetromino::L);
        CHECK(board.at({1, 2}) == Tetromino::L);
        CHECK(board.at({2, 2}) == Tetromino::L);
        CHECK(board.is_empty_square({0, 0}));
        CHECK(board.is_empty_square({0, 1}));
        CHECK(board.is_empty_square({0, 2}));
        CHECK(board.is_empty_square({2, 0}));
        CHECK(board.is_empty_square({2, 1}));
        CHECK(board.is_empty_square({3, 0}));
        CHECK(board.is_empty_square({3, 1}));
        CHECK(board.is_empty_square({3, 2}));

        revert_placement(board, {{1, 0}, Tetromino::L, Rotation::r0});
        CHECK(board.is_empty());
    }
}

}  // namespace tptps
