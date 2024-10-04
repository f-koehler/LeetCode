#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <vector>

class Solution {
  public:
    int removeElement(std::vector<int> &nums, int val) {
        if (nums.empty()) {
            return 0;
        }
        auto iter1 = nums.begin();
        auto iter2 = std::prev(nums.end());
        int counter = 0;
        while (iter1 != iter2) {
            if (*iter1 == val) {
                std::swap(*iter1, *iter2);
                --iter2;
                continue;
            }
            ++counter;
            ++iter1;
        }
        if (*iter1 != val) {
            ++counter;
        }
        return counter;
    }
};

TEST_CASE("0027 - Remove Element", "[Array][Two Pointers]") {
    Solution s;
    SECTION("Example 1") {
        std::vector<int> input{3, 2, 2, 3};
        const int result = s.removeElement(input, 3);
        std::cout << input[0] << input[1] << input[2] << input[3] << '\n';
        REQUIRE(result == 2);
        std::sort(input.begin(), input.end());
        REQUIRE(std::vector<int>(input.begin(), input.begin() + result) ==
                std::vector<int>{2, 2});
    }
    SECTION("Example 2") {
        std::vector<int> input{0, 1, 2, 2, 3, 0, 4, 2};
        const int result = s.removeElement(input, 2);
        REQUIRE(result == 5);
        std::sort(input.begin(), input.begin() + result);
        REQUIRE(std::vector<int>(input.begin(), input.begin() + result) ==
                std::vector<int>{0, 0, 1, 3, 4});
    }
}