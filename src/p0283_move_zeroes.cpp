#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P0283 {
    class Solution {
      public:
        void moveZeroes(std::vector<int> &nums) {
            // this is essentially an implementation of std::remove,
            // std::remove_if, etc.
            auto zero_iter = std::find(nums.begin(), nums.end(), 0);
            const auto end = nums.end();
            if (zero_iter == end) {
                return;
            }
            for (auto iter = zero_iter + 1; iter != end; ++iter) {
                if (*iter != 0) {
                    std::swap(*zero_iter, *iter);
                    ++zero_iter;
                }
            }
        }
    };

    TEST_CASE("0283 - Move Zeroes", "[Two Pointers][Array]") {
        Solution s;

        SECTION("Example 1") {
            std::vector<int> input{0, 1, 0, 3, 12};
            s.moveZeroes(input);
            REQUIRE(input == std::vector<int>{1, 3, 12, 0, 0});
        }
        SECTION("Example 2") {
            std::vector<int> input{0};
            s.moveZeroes(input);
            REQUIRE(input == std::vector<int>{0});
        }
        SECTION("Example 3") {
            std::vector<int> input{1};
            s.moveZeroes(input);
            REQUIRE(input == std::vector<int>{1});
        }
    }
} // namespace P0283
