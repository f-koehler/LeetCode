#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P0746 {
    class Solution {
      public:
        int minCostClimbingStairs(std::vector<int> &cost) {
            const std::size_t n = cost.size();
            for (std::size_t i = 2; i < n; ++i) {
                cost[i] += std::min(cost[i - 2], cost[i - 1]);
            }
            return std::min(cost[n - 2], cost[n - 1]);
        }
    };

    TEST_CASE("0746 - Min Cost Climbing Stairs",
              "[Array][Dynamic Programming]") {
        Solution s;
        SECTION("Example 1") {
            std::vector<int> cost{10, 15, 20};
            REQUIRE(s.minCostClimbingStairs(cost) == 15);
        }
        SECTION("Example 2") {
            std::vector<int> cost{1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
            REQUIRE(s.minCostClimbingStairs(cost) == 6);
        }
    }
} // namespace P0746
