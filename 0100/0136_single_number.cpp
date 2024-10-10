#include <catch2/catch_test_macros.hpp>
#include <functional>
#include <numeric>
#include <vector>

class Solution {
  public:
    int singleNumber(const std::vector<int> &nums) {
        // The xor of two numbers will be 0 if all bits are the same. Otherwise,
        // the different bits will be one in the output. Since we know that
        // there is a single unique number and all other numbers appear exactly
        // twice, we cann XOR all numbers together and should be left with the
        // bits of the unique number.
        return std::accumulate(nums.cbegin(), nums.cend(), 0,
                               std::bit_xor<int>{});
    }
};

TEST_CASE("0136 - Single Number", "[Array][Bit Manipulation]") {
    Solution s;

    SECTION("Example 1") {
        REQUIRE(s.singleNumber(std::vector<int>{2, 2, 1}) == 1);
    }
    SECTION("Example 2") {
        REQUIRE(s.singleNumber(std::vector<int>{4, 1, 2, 1, 2}) == 4);
    }
    SECTION("Example 3") { REQUIRE(s.singleNumber(std::vector<int>{1}) == 1); }
}