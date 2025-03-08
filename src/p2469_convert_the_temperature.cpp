#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>
using namespace std;

namespace P2469 {
    class Solution {
      public:
        vector<double> convertTemperature(double celsius) {
            return {celsius + 273.15, celsius * 1.8 + 32};
        }
    };

    TEST_CASE("2469 - Convert the Temperature", "[Math]") {
        Solution s;
        SECTION("Example 1") {
            auto result = s.convertTemperature(36.5);
            REQUIRE(result[0] == Catch::Approx(309.65));
            REQUIRE(result[1] == Catch::Approx(97.7));
        }
        SECTION("Example 2") {
            auto result = s.convertTemperature(122.11);
            REQUIRE(result[0] == Catch::Approx(395.26));
            REQUIRE(result[1] == Catch::Approx(251.798));
        }
    }
} // namespace P2469
