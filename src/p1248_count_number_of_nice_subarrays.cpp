#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P1248 {
    class Solution {
      public:
        int numberOfSubarrays(const std::vector<int> &nums, int k) {
            // count[i] is the number of ways to have i odd numbers
            std::vector<int> count(nums.size() + 1, 0);

            // there is 1 way of having 0 odd numbers
            count[0] = 1;

            // count of odd numbers in the current sequence
            int current_odd_count = 0;

            // the answer for this problem
            int num_nice_subarrays = 0;

            for (const int num : nums) {
                // increment current odd count if num is odd
                current_odd_count += num % 2;

                // we have reached the threshold for creating a nice subarray
                //
                // the number of new arrays depends on the number of ways to
                // reach current_odd_count - k
                if (current_odd_count >= k) {
                    num_nice_subarrays += count[current_odd_count - k];
                }

                // we found a new way of reaching the current odd count
                ++count[current_odd_count];
            }

            return num_nice_subarrays;
        }
    };

    TEST_CASE("1248 - Count Number of Nice Subarrays",
              "[Array][Hash Table][Math][Sliding Window][Prefix Sum]") {

        SECTION("Example 1") {
            // Input: nums = [1,1,2,1,1], k = 3
            // Output: 2
            Solution s;
            REQUIRE(s.numberOfSubarrays({1, 1, 2, 1, 1}, 3) == 2);
        }

        SECTION("Example 2") {
            // Input: nums = [2,4,6], k = 1
            // Output: 0
            Solution s;
            REQUIRE(s.numberOfSubarrays({2, 4, 6}, 1) == 0);
        }

        SECTION("Example 3") {
            // Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
            // Output: 16
            Solution s;
            REQUIRE(s.numberOfSubarrays({2, 2, 2, 1, 2, 2, 1, 2, 2, 2}, 2) ==
                    16);
        }
    }
} // namespace P1248
