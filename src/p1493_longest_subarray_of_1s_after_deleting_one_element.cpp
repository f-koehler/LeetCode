#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P1493 {
    class Solution {
      public:
        int longestSubarray(const std::vector<int> &nums) {
            // left bound of the sliding window
            int left = 0;

            // number of zeros in the current window
            int num_zeros = 0;

            int best_length = 0;

            const int length = nums.size();
            // apply a non-shrinking sliding window and keep track of the best
            // solution
            for (int right = 0; right < length; ++right) {
                if (nums[right] == 0) {
                    ++num_zeros;
                }

                if (num_zeros <= 1) {
                    // found a valid window, accept solution if larger
                    best_length = std::max(best_length, right - left);
                } else {
                    // advance left border by one
                    if (nums[left] == 0) {
                        --num_zeros;
                    }
                    ++left;
                }
            }
            return best_length;
        }
    };

    TEST_CASE("1493 - Longest Subarray of 1's After Deleting One Element",
              "[Array][Dynamic Programming][Sliding Window]") {

        SECTION("Example 1") {
            // Input: nums = [1,1,0,1]
            // Output: 3
            Solution s;
            REQUIRE(s.longestSubarray({1, 1, 0, 1}) == 3);
        }

        SECTION("Example 2") {
            // Input: nums = [0,1,1,1,0,1,1,0,1]
            // Output: 5
            Solution s;
            REQUIRE(s.longestSubarray({0, 1, 1, 1, 0, 1, 1, 0, 1}) == 5);
        }

        SECTION("Example 3") {
            // Input: nums = [1,1,1]
            // Output: 2
            Solution s;
            REQUIRE(s.longestSubarray({1, 1, 1}) == 2);
        }
    }
} // namespace P1493
