#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "../../src/lib/solver/board.hpp"

namespace tptps {

TEST_CASE("solver/board")
{
    SECTION("can get the number of columns and rows")
    {
        const Board board1{4, 3};
        const Board board2{3, 4};

        CHECK(board1.width() == 4);
        CHECK(board2.width() == 3);
        CHECK(board1.height() == 3);
        CHECK(board2.height() == 4);
    }

    SECTION("can change and check squares")
    {
        Board board{3, 4};

        CHECK(board.at({0, 2}) == Tetromino::empty);
        CHECK(board.is_empty_square({0, 2}));

        board.at({0, 2}) = Tetromino::T;

        CHECK(board.at({0, 2}) == Tetromino::T);
        CHECK(board.is_empty_square({0, 2}) == false);
    }

    SECTION("can check if the whole Board is empty or filled")
    {
        Board board{4, 3};

        // a new Board is empty
        CHECK(board.is_empty());
        CHECK(board.is_filled() == false);

        // JJ..
        // J...
        // J...
        board.at({0, 0}) = Tetromino::J;
        board.at({1, 0}) = Tetromino::J;
        board.at({0, 1}) = Tetromino::J;
        board.at({0, 2}) = Tetromino::J;
        CHECK(board.is_empty() == false);
        CHECK(board.is_filled() == false);

        // JJZ.
        // JZZ.
        // JZ..
        board.at({2, 0}) = Tetromino::Z;
        board.at({1, 1}) = Tetromino::Z;
        board.at({2, 1}) = Tetromino::Z;
        board.at({1, 2}) = Tetromino::Z;
        CHECK(board.is_empty() == false);
        CHECK(board.is_filled() == false);

        // JJZJ
        // JZZJ
        // JZJJ
        board.at({3, 0}) = Tetromino::J;
        board.at({3, 1}) = Tetromino::J;
        board.at({2, 2}) = Tetromino::J;
        board.at({3, 2}) = Tetromino::J;
        CHECK(board.is_empty() == false);
        CHECK(board.is_filled());
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
            board.at({1, 0}) = Tetromino::T;
            board.at({2, 0}) = Tetromino::T;
            board.at({3, 0}) = Tetromino::T;
            board.at({2, 1}) = Tetromino::T;
            board.at({0, 2}) = Tetromino::L;
            board.at({0, 3}) = Tetromino::L;
            board.at({0, 4}) = Tetromino::L;
            board.at({1, 4}) = Tetromino::L;
            board.at({1, 3}) = Tetromino::Z;
            board.at({2, 3}) = Tetromino::Z;
            board.at({2, 4}) = Tetromino::Z;
            board.at({3, 4}) = Tetromino::Z;

            CHECK_THAT(board.print(), Catch::Matchers::Equals(s));
        }

        SECTION("completed Board")
        {
            const std::string s = "JJZJ\n"
                                  "JZZJ\n"
                                  "JZJJ\n";

            Board board{4, 3};
            board.at({0, 0}) = Tetromino::J;
            board.at({1, 0}) = Tetromino::J;
            board.at({0, 1}) = Tetromino::J;
            board.at({0, 2}) = Tetromino::J;
            board.at({2, 0}) = Tetromino::Z;
            board.at({1, 1}) = Tetromino::Z;
            board.at({2, 1}) = Tetromino::Z;
            board.at({1, 2}) = Tetromino::Z;
            board.at({3, 0}) = Tetromino::J;
            board.at({3, 1}) = Tetromino::J;
            board.at({2, 2}) = Tetromino::J;
            board.at({3, 2}) = Tetromino::J;

            CHECK_THAT(board.print(), Catch::Matchers::Equals(s));
        }
    }
}

}  // namespace tptps
