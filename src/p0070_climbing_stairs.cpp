#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P0070 {
    class Solution {
      public:
        int climbStairs(int n) {
            int prev = 1;
            int prev_prev = 1;
            for (int k = 2; k <= n; ++k) {
                const int sum = prev + prev_prev;
                prev_prev = prev;
                prev = sum;
            }
            return prev;
        }
    };

    TEST_CASE("0070 - Climbing Stairs",
              "[Math][Dynamic Programming][Memoization]") {

        SECTION("Example 1") {
            // Input: n = 2
            // Output: 2
            Solution s;
            REQUIRE(s.climbStairs(2) == 2);
        }

        SECTION("Example 2") {
            // Input: n = 3
            // Output: 3
            Solution s;
            REQUIRE(s.climbStairs(3) == 3);
        }
    }
} // namespace P0070