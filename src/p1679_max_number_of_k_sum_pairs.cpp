#include <algorithm>
#include <cassert>
#include <catch2/catch_test_macros.hpp>
#include <unordered_map>
#include <vector>

namespace P1679 {
    class Solution {
      public:
        int maxOperations(const std::vector<int> &nums, int k) {
            // O(n) solution using hash table
            assert(!nums.empty());
            assert(k > 0);

            int result = 0;
            std::unordered_map<int, int> counts;

            for (const int num : nums) {
                ++counts[num];
            }

            for (const auto &[num, freq] : counts)
                if (const auto it = counts.find(k - num); it != counts.end())
                    result += std::min(freq, it->second);

            return result / 2;
        }
        int maxOperations2(std::vector<int> &nums, int k) {
            // O(n log n) solution using two pointers
            // an be faster for short inputs
            assert(!nums.empty());
            assert(k > 0);

            std::sort(nums.begin(), nums.end());

            int result = 0;
            int left = 0;
            int right = nums.size() - 1;
            while (left < right) {
                const int sum = nums[left] + nums[right];
                if (sum == k) {
                    ++left;
                    --right;
                    ++result;
                } else if (sum > k) {
                    --right;
                } else {
                    ++left;
                }
            }
            return result;
        }
    };

    TEST_CASE("1679 - Max Number of K-Sum Pairs",
              "[Array][Hash Table][Two Pointers][Sorting]") {

        SECTION("Example 1") {
            // Input: nums = [1,2,3,4], k = 5
            // Output: 2
            Solution s;
            std::vector<int> nums = {1, 2, 3, 4};
            REQUIRE(s.maxOperations(nums, 5) == 2);
            REQUIRE(s.maxOperations2(nums, 5) == 2);
        }

        SECTION("Example 2") {
            // Input: nums = [3,1,3,4,3], k = 6
            // Output: 1
            Solution s;
            std::vector<int> nums = {3, 1, 3, 4, 3};
            REQUIRE(s.maxOperations(nums, 6) == 1);
            REQUIRE(s.maxOperations2(nums, 6) == 1);
        }
    }
} // namespace P1679