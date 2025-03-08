#include <catch2/catch_test_macros.hpp>
#include <numeric>
#include <vector>

namespace P0724 {
    class Solution {
      public:
        int pivotIndex(const std::vector<int> &nums) {
            const std::size_t n = nums.size();
            if (n == 1) {
                // Here, both the left and right index are at the edege. Thus
                // prefix_sum==suffix_sum==0 and 0 should be returned.
                return 0;
            }

            int prefix_sum = 0;
            int suffix_sum = std::accumulate(nums.begin() + 1, nums.end(), 0);
            if (prefix_sum == suffix_sum) {
                return int{0};
            }
            for (std::size_t i = 1; i < n; ++i) {
                prefix_sum += nums[i - 1];
                suffix_sum -= nums[i];
                if (prefix_sum == suffix_sum) {
                    return i;
                }
            }
            return -1;
        }
    };

    TEST_CASE("0724 - Find Pivot Index", "[Array][Prefix Sum]") {
        Solution s;
        SECTION("Example 1") {
            REQUIRE(s.pivotIndex(std::vector<int>{1, 7, 3, 6, 5, 6}) == 3);
        }
        SECTION("Example 2") {
            REQUIRE(s.pivotIndex(std::vector<int>{1, 2, 3}) == -1);
        }
        SECTION("Example 3") {
            REQUIRE(s.pivotIndex(std::vector<int>{2, 1, -1}) == 0);
        }
        SECTION("Example 4") {
            REQUIRE(s.pivotIndex(std::vector<int>{42}) == 0);
        }
    }
} // namespace P0724