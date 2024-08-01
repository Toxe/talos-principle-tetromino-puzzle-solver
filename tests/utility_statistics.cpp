#include <algorithm>
#include <random>

#include "catch2/benchmark/catch_benchmark_all.hpp"
#include "catch2/catch_approx.hpp"
#include "catch2/catch_test_macros.hpp"

#include "../src/utility/statistics.hpp"

namespace tptps {

std::random_device rd;
std::mt19937 g(rd());

std::vector<double> gen_vector(std::size_t size)
{
    std::mt19937 gen(1234);
    std::uniform_int_distribution<> dist(1, 1000);
    std::vector<double> v(size);

    for (std::size_t i = 0; i < size; ++i)
        v[i] = dist(gen);

    return v;
}

TEST_CASE("utility/statistics")
{
    SECTION("mean")
    {
        CHECK(mean(std::vector<double>{3}) == Catch::Approx(3));
        CHECK(mean(std::vector<double>{5, 3}) == Catch::Approx(4));
        CHECK(mean(std::vector<double>{1, 2, 3, 4}) == Catch::Approx(2.5));
        CHECK(mean(std::vector<double>{2, 6, 4, 2, 1}) == Catch::Approx(3));
    }

    SECTION("median")
    {
        CHECK(median(std::vector<double>{3}) == Catch::Approx(3.0));
        CHECK(median(std::vector<double>{6, 4}) == Catch::Approx(5.0));
        CHECK(median(std::vector<double>{6, 1, 4}) == Catch::Approx(4.0));
        CHECK(median(std::vector<double>{6, 1, 4, 2}) == Catch::Approx(3.0));
        CHECK(median(std::vector<double>{6, 1, 4, 2, 9}) == Catch::Approx(4.0));
        CHECK(median(std::vector<double>{6, 1, 4, 2, 9, 1}) == Catch::Approx(3.0));
        CHECK(median(std::vector<double>{6, 1, 4, 2, 9, 1, 7}) == Catch::Approx(4.0));
        CHECK(median(std::vector<double>{6, 1, 4, 2, 9, 1, 7, 3}) == Catch::Approx(3.5));
        CHECK(median(std::vector<double>{6, 1, 4, 2, 9, 1, 7, 3, 6}) == Catch::Approx(4.0));

        const std::vector<double> v1(gen_vector(1000));
        const std::vector<double> v2(gen_vector(1001));

        CHECK(median(v1) == Catch::Approx(512.5));
        CHECK(median(v2) == Catch::Approx(514.0));
    }
}

}  // namespace tptps
