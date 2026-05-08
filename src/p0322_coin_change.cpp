#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <limits>
#include <vector>

namespace LeetCode::P0322 {
    class Solution {
      public:
        [[nodiscard]] static constexpr int
        coinChange(std::vector<int> &coins, const int total_amount) noexcept
            pre(!coins.empty() && (coins.size() <= 12) && (total_amount >= 0) &&
                (total_amount <= 10000))
                post(result : (result >= -1) && (result <= total_amount)) {
            // using std::array<int, 10001> since total_amount <= 10001, allows
            // us to make function constexpr
            std::array<int, 10001> dp;
            dp.fill(-1);

            dp[0] = 0;
            for (int amount = 1; amount <= total_amount; ++amount) {
                for (const auto coin : coins) {
                    contract_assert(
                        (coin > 0) &&
                        (coin <= std::numeric_limits<int32_t>::max()));

                    // compute the amount from which we can reach the current
                    // target amount with the current coin
                    const int previous_amount = amount - coin;

                    // current coin is larger than current target amount
                    if (previous_amount < 0) {
                        continue;
                    }

                    // we have not found a way to find the required previous
                    // amount
                    if (dp[previous_amount] == -1) {
                        // we could instead sort the coins and break early, but
                        // in my limited testing this approach is faster
                        continue;
                    }

                    // we have found a way to reach the current target amount
                    const int num_coins = dp[previous_amount] + 1;

                    // accept if it is the first way we have found for target
                    // amount so far
                    if (dp[amount] == -1) {
                        dp[amount] = num_coins;
                        continue;
                    }

                    // accept if it is better than our previous way
                    // (fewer_coins)
                    dp[amount] = std::min(dp[amount], num_coins);
                }
            }

            return dp[total_amount];
        }
    };

    TEST_CASE("0322 - Coin Change",
              "[Array][Dynamic Programming][Breadth-First Search]") {

        SECTION("Example 1") {
            // Input: coins = [1,2,5], amount = 11
            // Output: 3
            std::vector<int> coins{1, 2, 5};
            REQUIRE(Solution::coinChange(coins, 11) == 3);
        }

        SECTION("Example 2") {
            // Input: coins = [2], amount = 3
            // Output: -1
            std::vector<int> coins{2};
            REQUIRE(Solution::coinChange(coins, 3) == -1);
        }

        SECTION("Example 3") {
            // Input: coins = [1], amount = 0
            // Output: 0
            std::vector<int> coins{1};
            REQUIRE(Solution::coinChange(coins, 0) == 0);
        }
    }
} // namespace LeetCode::P0322
