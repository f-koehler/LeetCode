#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <functional>
#include <ranges>
#include <vector>

namespace P0268 {
    class Solution {
      public:
        [[nodiscard]] int missingNumber(const std::vector<int> &nums) {
            const int n = static_cast<int>(nums.size());
            // we can just xor to find the missing number, every other number
            // will appear twice (once in the nums array, once in the range of
            // all numbers [0,n])
            return std::ranges::fold_left(nums, int{0}, std::bit_xor<int>{}) ^
                   std::ranges::fold_left(std::views::iota(0, n + 1), int{0},
                                          std::bit_xor<int>{});
        }
    };

    TEST_CASE("0268 - Missing Number",
              "[Array][Hash Table][Math][Binary Search][Bit "
              "Manipulation][Sorting][NeetCode150]") {
        SECTION("Example 1") {
            REQUIRE(Solution{}.missingNumber({3, 0, 1}) == 2);
        }
        SECTION("Example 2") { REQUIRE(Solution{}.missingNumber({0, 1}) == 2); }
        SECTION("Example 3") {
            REQUIRE(Solution{}.missingNumber({9, 6, 4, 2, 3, 5, 7, 0, 1}) == 8);
        }
    }
} // namespace P0268