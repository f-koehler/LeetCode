#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <vector>

class Solution {
  public:
    std::vector<bool> kidsWithCandies(const std::vector<int> &candies,
                                      int extraCandies) {
        // we can safely dereference as the candies array is not empty
        const auto max_candies =
            *std::max_element(candies.cbegin(), candies.cend());

        std::vector<bool> result(candies.size(), false);

        std::transform(candies.cbegin(), candies.cend(), result.begin(),
                       [extraCandies, max_candies](int candies) {
                           return candies + extraCandies >= max_candies;
                       });
        return result;
    }
};

TEST_CASE("1431 - Kids With the Greatest Number of Candies", "[Array]") {
    Solution s;
    SECTION("Example 1") {
        REQUIRE(s.kidsWithCandies(std::vector<int>{2, 3, 5, 1, 3}, 3) ==
                std::vector<bool>{true, true, true, false, true});
    }
    SECTION("Example 2") {
        REQUIRE(s.kidsWithCandies(std::vector<int>{4, 2, 1, 1, 2}, 1) ==
                std::vector<bool>{true, false, false, false, false});
    }
    SECTION("Example 3") {
        REQUIRE(s.kidsWithCandies(std::vector<int>{12, 1, 12}, 10) ==
                std::vector<bool>{true, false, true});
    }
}