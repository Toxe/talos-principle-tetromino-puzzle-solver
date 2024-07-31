#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "../src/solver/board.hpp"

namespace tptps {

TEST_CASE("solver/board")
{
    SECTION("a new Board is empty")
    {
        const Board board{4, 3};

        for (Square::coordinates_type row = 0; row < 3; ++row)
            for (Square::coordinates_type col = 0; col < 4; ++col)
                CHECK(board.is_empty_square({col, row}));
    }

    SECTION("can get the number of columns and rows")
    {
        const Board board1{4, 3};
        const Board board2{3, 4};

        CHECK(board1.width() == 4);
        CHECK(board2.width() == 3);
        CHECK(board1.height() == 3);
        CHECK(board2.height() == 4);
    }

    SECTION("can check and place tetrominoes and check the content of squares")
    {
        Board board{4, 3};

        // check with empty Board
        CHECK(board.can_place({{0, 0}, Tetromino::I, Rotation::r0}, get_tetromino_placement_mask(Tetromino::I, Rotation::r0)));
        CHECK(board.can_place({{0, 0}, Tetromino::I, Rotation::r90}, get_tetromino_placement_mask(Tetromino::I, Rotation::r90)) == false);
        CHECK(board.can_place({{2, 0}, Tetromino::L, Rotation::r0}, get_tetromino_placement_mask(Tetromino::L, Rotation::r0)));
        CHECK(board.can_place({{3, 0}, Tetromino::L, Rotation::r0}, get_tetromino_placement_mask(Tetromino::L, Rotation::r0)) == false);
        CHECK(board.can_place({{1, 0}, Tetromino::L, Rotation::r270}, get_tetromino_placement_mask(Tetromino::L, Rotation::r270)));
        CHECK(board.can_place({{2, 0}, Tetromino::L, Rotation::r270}, get_tetromino_placement_mask(Tetromino::L, Rotation::r270)) == false);
        CHECK(board.can_place({{3, 0}, Tetromino::L, Rotation::r270}, get_tetromino_placement_mask(Tetromino::L, Rotation::r270)) == false);
        CHECK(board.can_place({{0, 0}, Tetromino::O, Rotation::r0}, get_tetromino_placement_mask(Tetromino::O, Rotation::r0)));

        board.place({{1, 0}, Tetromino::L, Rotation::r0});

        // .L..
        // .L..
        // .LL.
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

        CHECK(board.can_place({{2, 0}, Tetromino::T, Rotation::r90}, get_tetromino_placement_mask(Tetromino::T, Rotation::r90)));
        CHECK(board.can_place({{2, 0}, Tetromino::T, Rotation::r270}, get_tetromino_placement_mask(Tetromino::T, Rotation::r270)) == false);

        board.place({{2, 0}, Tetromino::T, Rotation::r90});

        // .L.T
        // .LTT
        // .LLT
        CHECK(board.at({3, 0}) == Tetromino::T);
        CHECK(board.at({2, 1}) == Tetromino::T);
        CHECK(board.at({3, 1}) == Tetromino::T);
        CHECK(board.at({3, 2}) == Tetromino::T);
        CHECK(board.is_empty_square({0, 0}));
        CHECK(board.is_empty_square({0, 1}));
        CHECK(board.is_empty_square({0, 2}));
        CHECK(board.is_empty_square({2, 0}));

        // check with mostly filled Board
        CHECK(board.can_place({{0, 0}, Tetromino::I, Rotation::r90}, get_tetromino_placement_mask(Tetromino::I, Rotation::r90)) == false);
        CHECK(board.can_place({{2, 0}, Tetromino::L, Rotation::r0}, get_tetromino_placement_mask(Tetromino::L, Rotation::r0)) == false);
        CHECK(board.can_place({{1, 0}, Tetromino::L, Rotation::r270}, get_tetromino_placement_mask(Tetromino::L, Rotation::r270)) == false);
        CHECK(board.can_place({{0, 0}, Tetromino::O, Rotation::r0}, get_tetromino_placement_mask(Tetromino::O, Rotation::r0)) == false);
    }

    SECTION("can check if the whole Board is filled")
    {
        Board board{4, 3};

        board.place({{0, 0}, Tetromino::J, Rotation::r180});
        board.place({{1, 0}, Tetromino::Z, Rotation::r90});
        board.place({{2, 0}, Tetromino::J, Rotation::r0});

        // JJZJ
        // JZZJ
        // JZJJ
        CHECK(board.is_finished());
    }

    SECTION("print Board")
    {
        SECTION("empty Board")
        {
            const std::string s = "....\n"
                                  "....\n"
                                  "....\n";

            const Board board{4, 3};

            CHECK_THAT(board.print(), Catch::Matchers::Equals(s));
        }

        SECTION("partially filled Board")
        {
            const std::string s = ".TTT\n"
                                  "..T.\n"
                                  "L...\n"
                                  "LZZ.\n"
                                  "LLZZ\n";

            Board board{4, 5};
            board.place({{1, 0}, Tetromino::T, Rotation::r0});
            board.place({{0, 2}, Tetromino::L, Rotation::r0});
            board.place({{1, 3}, Tetromino::Z, Rotation::r0});

            CHECK_THAT(board.print(), Catch::Matchers::Equals(s));
        }

        SECTION("completed Board")
        {
            const std::string s = "JJZJ\n"
                                  "JZZJ\n"
                                  "JZJJ\n";

            Board board{4, 3};
            board.place({{0, 0}, Tetromino::J, Rotation::r180});
            board.place({{1, 0}, Tetromino::Z, Rotation::r90});
            board.place({{2, 0}, Tetromino::J, Rotation::r0});

            CHECK_THAT(board.print(), Catch::Matchers::Equals(s));
        }
    }
}

}  // namespace tptps
