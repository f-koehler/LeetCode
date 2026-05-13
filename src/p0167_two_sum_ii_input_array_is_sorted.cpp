#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace LeetCode::P0167 {
    class Solution {
      public:
        [[nodiscard]] static std::vector<int>
        twoSum(const std::vector<int> &numbers, const int target)
            pre((numbers.size() >= 2) && (numbers.size() <= 30000) &&
                std::ranges::is_sorted(numbers) &&
                std::ranges::all_of(numbers,
                                    [](const int number) {
                                        return (number >= -1000) &&
                                               (number <= 1000);
                                    }) &&
                (target >= -1000) && (target <= 1000))
                post(result : (result.size() == 2) && (result[0] >= 1) &&
                     (result[1] <= numbers.size()) &&
                     (numbers[result[0] - 1] + numbers[result[1] - 1] ==
                      target)) {
            int left = 0;
            int right = numbers.size() - 1;
            while (left < right) {
                const int sum = numbers[left] + numbers[right];
                if (sum == target) {
                    // found the solution
                    return {left + 1, right + 1};
                }

                // if sum<target, our left element is too small to reach the
                // target with any number, increase left bound
                if (sum < target) {
                    ++left;
                } else {
                    // symmetric: if sum> target, our right element is too large
                    // to reach the target with any number
                    --right;
                }
            }
            // there always should be solution as per problem description
            return {};
        }
    };

    TEST_CASE("0167 - Two Sum II - Input Array Is Sorted",
              "[Array][Two Pointers][Binary Search]") {

        SECTION("Example 1") {
            // Input: numbers = [2,7,11,15], target = 9
            // Output: [1,2]
            REQUIRE(Solution::twoSum(std::vector<int>{2, 7, 11, 15}, 9) ==
                    std::vector<int>{1, 2});
        }

        SECTION("Example 2") {
            // Input: numbers = [2,3,4], target = 6
            // Output: [1,3]
            REQUIRE(Solution::twoSum(std::vector<int>{2, 3, 4}, 6) ==
                    std::vector<int>{1, 3});
        }

        SECTION("Example 3") {
            // Input: numbers = [-1,0], target = -1
            // Output: [1,2]
            REQUIRE(Solution::twoSum(std::vector<int>{-1, 0}, -1) ==
                    std::vector<int>{1, 2});
        }
    }
} // namespace LeetCode::P0167
