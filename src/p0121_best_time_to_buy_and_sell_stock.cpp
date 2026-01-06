#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P0121 {
    class Solution {
      public:
        int maxProfit(const std::vector<int> &prices) {
            int max_profit = 0;
            int min_price = prices.front();
            for (int price : prices) {
                max_profit = std::max(max_profit, price - min_price);
                min_price = std::min(min_price, price);
            }
            return max_profit;
        }
    };

    TEST_CASE("0121 - Best Time to Buy and Sell Stock",
              "[Array][Dynamic Programming][NeetCode150]") {

        SECTION("Example 1") {
            // Input: prices = [7,1,5,3,6,4]
            // Output: 5
            Solution s;
            REQUIRE(s.maxProfit({7, 1, 5, 3, 6, 4}) == 5);
        }

        SECTION("Example 2") {
            // Input: prices = [7,6,4,3,1]
            // Output: 0
            Solution s;
            REQUIRE(s.maxProfit({7, 6, 4, 3, 1}) == 0);
        }
    }
} // namespace P0121
