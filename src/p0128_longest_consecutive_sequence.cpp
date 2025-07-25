#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <unordered_set>
#include <vector>

namespace P0128 {
    class Solution {
      public:
        int longestConsecutive(const std::vector<int> &nums) {
            if (nums.size() < 2) {
                return nums.size();
            }

            // step 1 - build an hashset of all numbers
            // inserting of one element: O(1)
            // total complexity: O(n)
            std::unordered_set<int> set(nums.cbegin(), nums.cend());

            // step 2 - grow subsequnces from all possible starting numbers and
            // fint the longest one
            std::size_t longest_sequence = 0;
            for (int num : nums) {
                if (set.contains(num - 1)) {
                    // num is not the start of a sequence
                    continue;
                }

                // num is the start of a sequence, start growing it
                std::size_t length = 1;
                while (set.contains(++num)) {
                    ++length;
                }
                longest_sequence = std::max(longest_sequence, length);
            }
            return longest_sequence;
        }
    };

    TEST_CASE("0128 - Longest Consecutive Sequence",
              "[Array][Hash Table][Union Find]") {

        SECTION("Example 1") {
            // Input: nums = [100,4,200,1,3,2]
            // Output: 4
            Solution s;
            REQUIRE(s.longestConsecutive({100, 4, 200, 1, 3, 2}) == 4);
        }

        SECTION("Example 2") {
            // Input: nums = [0,3,7,2,5,8,4,6,0,1]
            // Output: 9
            Solution s;
            REQUIRE(s.longestConsecutive({0, 3, 7, 2, 5, 8, 4, 6, 0, 1}) == 9);
        }

        SECTION("Example 3") {
            // Input: nums = [1,0,1,2]
            // Output: 3
            Solution s;
            REQUIRE(s.longestConsecutive({1, 0, 1, 2}) == 3);
        }
    }
} // namespace P0128
