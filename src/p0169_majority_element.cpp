#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P0169 {
    class Solution {
      public:
        int majorityElement(const std::vector<int> &nums) {
            int candidate = 0;
            int candidate_count = 0;
            for (int number : nums) {
                if (candidate_count > 0) {
                    candidate_count += (candidate == number) ? +1 : -1;
                    continue;
                }
                candidate = number;
                candidate_count = 1;
            }
            return candidate;
        }
    };

    TEST_CASE("0169 - Majority Element",
              "[Array][Hash Table][Divide and Conquer][Sorting][Counting]") {

        SECTION("Example 1") {
            // Input: nums = [3,2,3]
            // Output: 3
            Solution s;
            REQUIRE(s.majorityElement({3, 2, 3}) == 3);
        }

        SECTION("Example 2") {
            // Input: nums = [2,2,1,1,1,2,2]
            // Output: 2
            Solution s;
            REQUIRE(s.majorityElement({2, 2, 1, 1, 1, 2, 2}) == 2);
        }
    }
} // namespace P0169
