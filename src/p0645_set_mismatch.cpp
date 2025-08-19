#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <ranges>
#include <vector>

namespace P0645 {
    class Solution {
      public:
        std::vector<int> findErrorNums(const std::vector<int> &nums) {
            std::vector<bool> found(nums.size() + 1, false);
            found[0] = true;
            int duplicate_number = -1;
            for (int num : nums) {
                if (found[num]) {
                    duplicate_number = num;
                    continue;
                }
                found[num] = true;
            }
            int missing_number = static_cast<int>(
                std::distance(found.cbegin(),
                              std::find(found.cbegin(), found.cend(), false)));
            return std::vector<int>{duplicate_number, missing_number};
        }
    };

    TEST_CASE("0645 - Set Mismatch",
              "[Array][Hash Table][Bit Manipulation][Sorting]") {

        SECTION("Example 1") {
            // Input: nums = [1,2,2,4]
            // Output: [2,3]
            Solution s;
            std::vector<int> result = s.findErrorNums({1, 2, 2, 4});
            std::ranges::sort(result);
            REQUIRE(result == std::vector<int>{2, 3});
        }

        SECTION("Example 2") {
            // Input: nums = [1,1]
            // Output: [1,2]
            Solution s;
            std::vector<int> result = s.findErrorNums({1, 1});
            std::ranges::sort(result);
            REQUIRE(result == std::vector<int>{1, 2});
        }
    }
} // namespace P0645
