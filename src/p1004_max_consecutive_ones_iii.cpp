#include <algorithm>
#include <cassert>
#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P1004 {
    class Solution {
      public:
        int longestOnes(const std::vector<int> &nums, int k) {
            assert(!nums.empty());
            assert(k >= 0);
            assert(k < nums.size());
            assert(std::all_of(nums.cbegin(), nums.cend(),
                               [](int n) { return (n == 0) || (n == 1); }));
            const int n = nums.size();
            int left = 0;
            int right = 0;
            int max_len = 0;
            while (right < n) {
                if (nums[right] == 0) {
                    // flip the zero
                    --k;
                }

                while (k < 0) {
                    // move left pointer to ensure we do not have flipped to
                    // many 0s
                    if (nums[left] == 0) {
                        ++k;
                    }
                    ++left;
                }

                // move right pointer
                ++right;

                // update maximum length
                max_len = std::max(max_len, right - left);
            }
            return max_len;
        }
    };

    TEST_CASE("1004 - Max Consecutive Ones III",
              "[Array][Binary Search][Sliding Window][Prefix Sum]") {

        SECTION("Example 1") {
            // Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
            // Output: 6
            Solution s;
            REQUIRE(s.longestOnes({1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0}, 2) == 6);
        }

        SECTION("Example 2") {
            // Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
            // Output: 10
            Solution s;
            REQUIRE(s.longestOnes({0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0,
                                   1, 1, 1, 1},
                                  3) == 10);
        }
    }
} // namespace P1004