#include <catch2/catch_test_macros.hpp>
#include <vector>

class Solution {
  public:
    bool increasingTriplet(const std::vector<int> &nums) {
        int first = std::numeric_limits<int>::max();
        int second = std::numeric_limits<int>::max();

        for (const int &number : nums) {
            if (number <= first) {
                first = number;
                continue;
            }
            if (number <= second) {
                second = number;
                continue;
            }
            return true;
        }

        return false;
    }
};

TEST_CASE("0334 - Increasing Triplet Subsequence", "[Array][Greedy]") {
    Solution s;
    SECTION("Example 1") { REQUIRE(s.increasingTriplet({1, 2, 3, 4, 5})); }
    SECTION("Example 2") { REQUIRE(!s.increasingTriplet({5, 4, 3, 2, 1})); }

    SECTION("Example 3") { REQUIRE(s.increasingTriplet({2, 1, 5, 0, 4, 6})); }
    SECTION("Example 4") {
        REQUIRE(!s.increasingTriplet(
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
             1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
             1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
             1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
             1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
             1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
             1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
             1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
             1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    }
}
