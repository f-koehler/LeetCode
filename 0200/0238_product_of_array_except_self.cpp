#include <catch2/catch_test_macros.hpp>
#include <vector>

class Solution {
  public:
    std::vector<int> productExceptSelf(const std::vector<int> &nums) {
        const std::size_t n = nums.size();
        std::vector<int> result(n, 1);

        // fill ith element with the prefix product of all prior elements
        for (std::size_t i = 1; i < n; ++i) {
            result[i] = result[i - 1] * nums[i - 1];
        }

        // build the suffix product up to i from the right
        int suffix = 1;
        for (std::size_t i = n - 1; i > 0; --i) {
            result[i] *= suffix;
            suffix *= nums[i];
        }
        // do i=0 separately to prevent integer underflow
        result[0] *= suffix;

        return result;
    }
};

TEST_CASE("206 - Product of Array Except Self", "[Array][Prefix Sum]") {
    Solution s;
    SECTION("Example 1") {
        REQUIRE(s.productExceptSelf({1, 2, 3, 4}) ==
                std::vector<int>{24, 12, 8, 6});
    }
    SECTION("Example 2") {
        REQUIRE(s.productExceptSelf({-1, 1, 0, -3, 3}) ==
                std::vector<int>{{0, 0, 9, 0, 0}});
    }
}