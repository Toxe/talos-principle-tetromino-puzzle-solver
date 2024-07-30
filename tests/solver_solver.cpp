#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_all.hpp"

#include "../src/solver/solver.hpp"

namespace tptps {

TEST_CASE("solver/solver")
{
    SECTION("find all possible placements for a tetromino with a certain rotation on the Board")
    {
        SECTION("empty Board")
        {
            Board board{4, 4};

            const auto placements_r0 = find_possible_placements(board, Tetromino::L, Rotation::r0);
            const auto placements_r90 = find_possible_placements(board, Tetromino::L, Rotation::r90);

            CHECK_THAT(placements_r0, Catch::Matchers::SizeIs(6));
            CHECK_THAT(placements_r90, Catch::Matchers::SizeIs(6));

            CHECK_THAT(placements_r0, Catch::Matchers::UnorderedRangeEquals(std::vector<Placement>{
                                          {{0, 0}, Tetromino::L, Rotation::r0},
                                          {{1, 0}, Tetromino::L, Rotation::r0},
                                          {{2, 0}, Tetromino::L, Rotation::r0},
                                          {{0, 1}, Tetromino::L, Rotation::r0},
                                          {{1, 1}, Tetromino::L, Rotation::r0},
                                          {{2, 1}, Tetromino::L, Rotation::r0},
                                      }));

            CHECK_THAT(placements_r90, Catch::Matchers::UnorderedRangeEquals(std::vector<Placement>{
                                           {{0, 0}, Tetromino::L, Rotation::r90},
                                           {{1, 0}, Tetromino::L, Rotation::r90},
                                           {{0, 1}, Tetromino::L, Rotation::r90},
                                           {{1, 1}, Tetromino::L, Rotation::r90},
                                           {{0, 2}, Tetromino::L, Rotation::r90},
                                           {{1, 2}, Tetromino::L, Rotation::r90},
                                       }));
        }

        SECTION("partially filled Board with enough empty squares")
        {
            Board board{4, 4};

            // LLL.
            // LZ..
            // ZZ..
            // Z...
            board.place({{0, 0}, Tetromino::L, Rotation::r90});
            board.place({{0, 1}, Tetromino::Z, Rotation::r90});

            const std::vector<Placement> placements_r0 = find_possible_placements(board, Tetromino::T, Rotation::r0);
            const std::vector<Placement> placements_r90 = find_possible_placements(board, Tetromino::T, Rotation::r90);
            const std::vector<Placement> placements_r180 = find_possible_placements(board, Tetromino::T, Rotation::r180);
            const std::vector<Placement> placements_r270 = find_possible_placements(board, Tetromino::T, Rotation::r270);

            CHECK_THAT(placements_r0, Catch::Matchers::SizeIs(0));
            CHECK_THAT(placements_r90, Catch::Matchers::SizeIs(2));
            CHECK_THAT(placements_r180, Catch::Matchers::SizeIs(1));
            CHECK_THAT(placements_r270, Catch::Matchers::SizeIs(1));

            CHECK_THAT(placements_r90, Catch::Matchers::UnorderedRangeEquals(std::vector<Placement>{
                                           {{2, 0}, Tetromino::T, Rotation::r90},
                                           {{2, 1}, Tetromino::T, Rotation::r90},
                                       }));
            CHECK_THAT(placements_r180, Catch::Matchers::UnorderedRangeEquals(std::vector<Placement>{{{1, 2}, Tetromino::T, Rotation::r180}}));
            CHECK_THAT(placements_r270, Catch::Matchers::UnorderedRangeEquals(std::vector<Placement>{{{2, 1}, Tetromino::T, Rotation::r270}}));
        }

        SECTION("partially filled Board without enough space")
        {
            Board board{4, 4};

            // LLL.
            // LZ..
            // ZZOO
            // Z.OO
            board.place({{0, 0}, Tetromino::L, Rotation::r90});
            board.place({{0, 1}, Tetromino::Z, Rotation::r90});
            board.place({{2, 2}, Tetromino::O, Rotation::r0});

            CHECK(find_possible_placements(board, Tetromino::T, Rotation::r0).empty());
            CHECK(find_possible_placements(board, Tetromino::T, Rotation::r90).empty());
        }

        SECTION("full Board")
        {
            Board board{4, 3};

            board.place({{0, 0}, Tetromino::L, Rotation::r90});
            board.place({{0, 1}, Tetromino::T, Rotation::r180});
            board.place({{2, 0}, Tetromino::T, Rotation::r90});

            // LLLT
            // LtTT
            // tttT
            CHECK(find_possible_placements(board, Tetromino::L, Rotation::r0).empty());
            CHECK(find_possible_placements(board, Tetromino::L, Rotation::r90).empty());
        }
    }

    SECTION("generate a list of all possible placements for a tetromino on the Board")
    {
        SECTION("empty Board")
        {
            Board board{4, 4};

            const auto placements = get_all_possible_placements(board, Tetromino::L);

            CHECK_THAT(placements, Catch::Matchers::SizeIs(24));
            CHECK_THAT(placements, Catch::Matchers::UnorderedRangeEquals(std::vector<Placement>{
                                       {{0, 0}, Tetromino::L, Rotation::r0},
                                       {{1, 0}, Tetromino::L, Rotation::r0},
                                       {{2, 0}, Tetromino::L, Rotation::r0},
                                       {{0, 1}, Tetromino::L, Rotation::r0},
                                       {{1, 1}, Tetromino::L, Rotation::r0},
                                       {{2, 1}, Tetromino::L, Rotation::r0},
                                       {{0, 0}, Tetromino::L, Rotation::r90},
                                       {{1, 0}, Tetromino::L, Rotation::r90},
                                       {{0, 1}, Tetromino::L, Rotation::r90},
                                       {{1, 1}, Tetromino::L, Rotation::r90},
                                       {{0, 2}, Tetromino::L, Rotation::r90},
                                       {{1, 2}, Tetromino::L, Rotation::r90},
                                       {{0, 0}, Tetromino::L, Rotation::r180},
                                       {{1, 0}, Tetromino::L, Rotation::r180},
                                       {{2, 0}, Tetromino::L, Rotation::r180},
                                       {{0, 1}, Tetromino::L, Rotation::r180},
                                       {{1, 1}, Tetromino::L, Rotation::r180},
                                       {{2, 1}, Tetromino::L, Rotation::r180},
                                       {{0, 0}, Tetromino::L, Rotation::r270},
                                       {{1, 0}, Tetromino::L, Rotation::r270},
                                       {{0, 1}, Tetromino::L, Rotation::r270},
                                       {{1, 1}, Tetromino::L, Rotation::r270},
                                       {{0, 2}, Tetromino::L, Rotation::r270},
                                       {{1, 2}, Tetromino::L, Rotation::r270},
                                   }));
        }

        SECTION("partially filled Board with enough empty squares")
        {
            Board board{4, 4};

            // LLL.
            // LZ..
            // ZZ..
            // Z...
            board.place({{0, 0}, Tetromino::L, Rotation::r90});
            board.place({{0, 1}, Tetromino::Z, Rotation::r90});

            const std::vector<Placement> placements = get_all_possible_placements(board, Tetromino::T);

            CHECK_THAT(placements, Catch::Matchers::SizeIs(4));
            CHECK_THAT(placements, Catch::Matchers::UnorderedRangeEquals(std::vector<Placement>{
                                       {{2, 0}, Tetromino::T, Rotation::r90},
                                       {{2, 1}, Tetromino::T, Rotation::r90},
                                       {{1, 2}, Tetromino::T, Rotation::r180},
                                       {{2, 1}, Tetromino::T, Rotation::r270},
                                   }));
        }

        SECTION("partially filled Board without enough space")
        {
            Board board{4, 4};

            // LLL.
            // LZ..
            // ZZOO
            // Z.OO
            board.place({{0, 0}, Tetromino::L, Rotation::r90});
            board.place({{0, 1}, Tetromino::Z, Rotation::r90});
            board.place({{2, 2}, Tetromino::O, Rotation::r0});

            const auto placements = get_all_possible_placements(board, Tetromino::T);

            CHECK(placements.empty());
        }

        SECTION("full Board")
        {
            Board board{4, 3};

            board.place({{0, 0}, Tetromino::L, Rotation::r90});
            board.place({{0, 1}, Tetromino::T, Rotation::r180});
            board.place({{2, 0}, Tetromino::T, Rotation::r90});

            // LLLT
            // LtTT
            // tttT
            const auto placements = get_all_possible_placements(board, Tetromino::L);

            CHECK(placements.empty());
        }
    }

    SECTION("solve puzzles")
    {
        SolverStats stats;

        SECTION("World Hub A")
        {
            SECTION("Tutorial Puzzle")
            {
                const auto solution = solve_puzzle(Board{4, 3}, {Tetromino::J, Tetromino::J, Tetromino::Z}, stats);

                REQUIRE(solution.has_value());
                CHECK(solution->is_finished());
                CHECK(solution->width() == 4);
                CHECK(solution->height() == 3);
            }

            SECTION("Gate A")
            {
                const auto solution = solve_puzzle(Board{4, 4}, {Tetromino::I, Tetromino::Z, Tetromino::J, Tetromino::L}, stats);

                REQUIRE(solution.has_value());
                CHECK(solution->is_finished());
                CHECK(solution->width() == 4);
                CHECK(solution->height() == 4);
            }

            SECTION("Laser Connector")
            {
                const auto solution = solve_puzzle(Board{4, 3}, {Tetromino::L, Tetromino::T, Tetromino::T}, stats);

                REQUIRE(solution.has_value());
                CHECK(solution->is_finished());
                CHECK(solution->width() == 4);
                CHECK(solution->height() == 3);
            }

            SECTION("Cube")
            {
                const auto solution = solve_puzzle(Board{4, 4}, {Tetromino::L, Tetromino::T, Tetromino::T, Tetromino::Z}, stats);

                REQUIRE(solution.has_value());
                CHECK(solution->is_finished());
                CHECK(solution->width() == 4);
                CHECK(solution->height() == 4);
            }
        }

        SECTION("World Hub B")
        {
            SECTION("Gate B")
            {
                const auto solution = solve_puzzle(Board{4, 5}, {Tetromino::I, Tetromino::T, Tetromino::T, Tetromino::L, Tetromino::Z}, stats);

                REQUIRE(solution.has_value());
                CHECK(solution->is_finished());
                CHECK(solution->width() == 4);
                CHECK(solution->height() == 5);
            }

            SECTION("Fan")
            {
                const auto solution = solve_puzzle(Board{4, 5}, {Tetromino::T, Tetromino::T, Tetromino::L, Tetromino::S, Tetromino::Z}, stats);

                REQUIRE(solution.has_value());
                CHECK(solution->is_finished());
                CHECK(solution->width() == 4);
                CHECK(solution->height() == 5);
            }

            SECTION("Recording")
            {
                const auto solution = solve_puzzle(Board{4, 5}, {Tetromino::S, Tetromino::Z, Tetromino::J, Tetromino::T, Tetromino::T}, stats);

                REQUIRE(solution.has_value());
                CHECK(solution->is_finished());
                CHECK(solution->width() == 4);
                CHECK(solution->height() == 5);
            }
        }

        SECTION("World Hub C")
        {
            SECTION("Gate C")
            {
                const auto solution = solve_puzzle(Board{4, 6}, {{Tetromino::L, Tetromino::J, Tetromino::J, Tetromino::T, Tetromino::T, Tetromino::Z}}, stats);

                REQUIRE(solution.has_value());
                CHECK(solution->is_finished());
                CHECK(solution->width() == 4);
                CHECK(solution->height() == 6);
            }

            SECTION("Platform")
            {
                const auto solution = solve_puzzle(Board{4, 6}, {{Tetromino::O, Tetromino::I, Tetromino::Z, Tetromino::L, Tetromino::T, Tetromino::T}}, stats);

                REQUIRE(solution.has_value());
                CHECK(solution->is_finished());
                CHECK(solution->width() == 4);
                CHECK(solution->height() == 6);
            }
        }
    }
}

}  // namespace tptps
