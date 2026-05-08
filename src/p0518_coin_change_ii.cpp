#include <catch2/catch_test_macros.hpp>
#include <numeric>
#include <vector>

namespace LeetCode::P0518 {
    class Solution {
      public:
        [[nodiscard]] static constexpr int
        change(const int total_amount, std::vector<int> &coins) noexcept
            pre((total_amount >= 0) && (total_amount <= 5000) &&
                !coins.empty() && coins.size() <= 300)

                post(result : result >= 0) {
            // the intermediate results can grow quite large for some of the
            // test cases -> uint64_t (int64_t is not enough) only the final
            // result is guaranteed to fit into 32bit signed integer
            std::array<uint64_t, 5001> combinations;
            combinations.fill(0);

            // starting condition for amount 0 (example consider reaching amount
            // 1 with 1 coin: combinations[1] = combinations[0], has to be one)
            combinations[0] = 1;

            // We have to be careful here to count combinations and not
            // permutations.
            //
            // Example: coins=[2,1], amount=3
            // Both permutations [1,2] and [2,1] are valid solutions, but they
            // are only one combination of elements.
            //
            // We start with one coin and find all the amounts we can reach with
            // just that coin. Then we move to the next coin and check how many
            // amounts we can reach using just this coin and the previous one.
            // And so on. Once we are done with one coin we are not using it
            // again to avoid counting another permutation for the same
            // combination of coins. This means that compared to P0322 Coin
            // Change, the loop order is swapped.
            for (const int coin : coins) {
                contract_assert((coin > 0) && (coin <= 5000));
                for (int amount = coin; amount <= total_amount; ++amount) {
                    combinations[amount] += combinations[amount - coin];
                }
            }

            return static_cast<int>(combinations[total_amount]);
        }
    };

    TEST_CASE("0518 - Coin Change II", "[Array][Dynamic Programming]") {

        SECTION("Example 1") {
            // Input: amount = 5, coins = [1,2,5]
            // Output: 4
            std::vector<int> coins{1, 2, 5};
            REQUIRE(Solution::change(5, coins) == 4);
        }

        SECTION("Example 2") {
            // Input: amount = 3, coins = [2]
            // Output: 0
            std::vector<int> coins{2};
            REQUIRE(Solution::change(3, coins) == 0);
        }

        SECTION("Example 3") {
            // Input: amount = 10, coins = [10]
            // Output: 1
            std::vector<int> coins{10};
            REQUIRE(Solution::change(10, coins) == 1);
        }
    }
} // namespace LeetCode::P0518
