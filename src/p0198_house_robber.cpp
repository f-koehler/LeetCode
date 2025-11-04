#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P0198 {
    class Solution {
      public:
        int rob(const std::vector<int> &nums) {
            // pad with two empty houses
            int profit_prev_prev = 0;
            int profit_prev = 0;
            for (int house : nums) {
                // compute the best profit up to this point:
                // either rob this house and combine with i-2 solution
                // or do not rob this house and use i-1 solution
                // whichever is higher
                const int profit =
                    std::max(profit_prev, profit_prev_prev + house);
                profit_prev_prev = profit_prev;
                profit_prev = profit;
            }
            return profit_prev;
        }
    };

    TEST_CASE("0198 - House Robber", "[Array][Dynamic Programming]") {

        SECTION("Example 1") {
            // Input: nums = [1,2,3,1]
            // Output: 4
            Solution s;
            REQUIRE(s.rob({1, 2, 3, 1}) == 4);
        }

        SECTION("Example 2") {
            // Input: nums = [2,7,9,3,1]
            // Output: 12
            Solution s;
            REQUIRE(s.rob({2, 7, 9, 3, 1}) == 12);
        }

        SECTION("Example 3") {
            // Input: nums = [2,1,1,2]
            // Output: 4
            Solution s;
            REQUIRE(s.rob({2, 1, 1, 2}) == 4);
        }
    }
} // namespace P0198