#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <vector>

class Solution {
  public:
    int largestAltitude(const std::vector<int> &gain) {
        int altitude = 0;
        int max_altitude = 0;
        for (int change : gain) {
            altitude += change;
            max_altitude = std::max(max_altitude, altitude);
        }
        return max_altitude;
    }
};

TEST_CASE("1732 - Find the Highest Altitude", "[Array][Prefix Sum]") {
    Solution s;
    SECTION("Example 1") {
        REQUIRE(s.largestAltitude(std::vector<int>{-5, 1, 5, 0, -7}) == 1);
    }
    SECTION("Example 2") {
        REQUIRE(s.largestAltitude(std::vector<int>{-4, -3, -2, -1, 4, 3, 2}) ==
                0);
    }
}