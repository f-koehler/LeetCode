#include <catch2/catch_test_macros.hpp>
#include <ranges>
#include <vector>

namespace P0055 {
    class Solution {
      public:
        bool canJump(const std::vector<int> &nums) {
            // idea:
            // 1. start from the end of the array
            // 2. check if we can reach the goal -> move goal post to the
            // current index
            // 3. repeat and check if we can reach to or beyond the new goal
            // post
            std::size_t goal_post = nums.size() - 1;
            for (auto [index, jump_distance] : std::ranges::views::reverse(
                     std::ranges::views::enumerate(nums))) {
                if (index + static_cast<std::size_t>(jump_distance) >=
                    goal_post) {
                    goal_post = index;
                }
            }

            return goal_post == 0;
        }
    };

    TEST_CASE("0055 - Jump Game", "[Array][Dynamic Programming][Greedy]") {

        SECTION("Example 1") {
            // Input: nums = [2,3,1,1,4]
            // Output: true
            Solution s;
            REQUIRE(s.canJump({2, 3, 1, 1, 4}));
        }

        SECTION("Example 2") {
            // Input: nums = [3,2,1,0,4]
            // Output: false
            Solution s;
            REQUIRE(s.canJump({2, 3, 1, 0, 4}));
        }
    }
} // namespace P0055
