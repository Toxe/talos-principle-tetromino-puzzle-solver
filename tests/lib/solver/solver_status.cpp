#include <thread>

#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "../../src/lib/solver/solver_status.hpp"

using namespace std::literals::chrono_literals;

namespace tptps {

TEST_CASE("solver/solver_status")
{
    SECTION("start, stop and measure duration")
    {
        SolverStatus status;

        // stopped
        CHECK(status.is_running() == false);
        CHECK(status.duration() == 0ms);

        // start and wait for a short while
        status.start();
        std::this_thread::sleep_for(1ms);

        CHECK(status.is_running());
        CHECK(status.duration() > 1ms);

        // stop
        status.stop();

        CHECK(status.is_running() == false);
    }

    SECTION("calling start() multiple times is not resetting duration")
    {
        SolverStatus status;

        status.start();
        const auto dur1 = status.duration();

        std::this_thread::sleep_for(10ms);
        const auto dur2 = status.duration();

        status.start();  // already running
        const auto dur3 = status.duration();

        std::this_thread::sleep_for(1ms);

        status.start();  // already running
        const auto dur4 = status.duration();

        CHECK(dur2 > dur1);
        CHECK(dur3 > dur2);
        CHECK(dur4 > dur3);
        CHECK(status.duration() > dur1);
        CHECK(status.duration() > dur2);
        CHECK(status.duration() > dur3);
        CHECK(status.duration() > dur4);
    }

    SECTION("once stopped, duration is not changing anymore, even when calling stop() multiple times")
    {
        SolverStatus status;

        status.start();
        status.stop();
        const auto dur1 = status.duration();

        std::this_thread::sleep_for(1ms);

        status.stop();  // already stopped
        const auto dur2 = status.duration();

        std::this_thread::sleep_for(1ms);

        status.stop();  // already stopped
        const auto dur3 = status.duration();

        CHECK(status.duration() == dur1);
        CHECK(status.duration() == dur2);
        CHECK(status.duration() == dur3);
    }

    SECTION("can update stats")
    {
        SolverStatus status;

        CHECK(status.function_called() == 0);
        CHECK(status.placements_calculated() == 0);

        status.add_function_called();
        CHECK(status.function_called() == 1);
        CHECK(status.placements_calculated() == 0);

        status.add_placements_calculated(5);
        CHECK(status.function_called() == 1);
        CHECK(status.placements_calculated() == 5);
    }

    SECTION("automatically starts when updating values")
    {
        SolverStatus status;

        CHECK(status.is_running() == false);

        status.add_function_called();

        CHECK(status.is_running());
    }

    SECTION("logging")
    {
        std::setlocale(LC_ALL, "en_US.utf8");

        SECTION("can generate log lines with and without a prefix")
        {
            SolverStatus status1;
            SolverStatus status2{"prefix"};

            CHECK_THAT(status1.build_log_message(), Catch::Matchers::Equals("    0.000 ns (calls: 0, calculations: 0)"));
            CHECK_THAT(status2.build_log_message(), Catch::Matchers::StartsWith("prefix "));
        }

        SECTION("can generate log lines whether logging is enabled or not")
        {
            SolverStatus status1{"prefix", false};
            SolverStatus status2{"prefix", true};

            CHECK_THAT(status1.build_log_message(), Catch::Matchers::StartsWith("prefix "));
            CHECK_THAT(status2.build_log_message(), Catch::Matchers::StartsWith("prefix "));
        }

        SECTION("can add a suffix to log lines")
        {
            SolverStatus status{"prefix"};

            CHECK_THAT(status.build_log_message("end"), Catch::Matchers::EndsWith("end"));
            CHECK_THAT(status.build_log_message("suffix"), Catch::Matchers::EndsWith("suffix"));
        }
    }
}

}  // namespace tptps
