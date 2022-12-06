#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <vector>
using namespace std;

class Solution {
  public:
    vector<int> getConcatenation(vector<int> &nums) {
        vector<int> ans(2 * nums.size(), 0);
        copy(nums.begin(), nums.end(), ans.begin());
        copy(nums.begin(), nums.end(), ans.begin() + nums.size());
        return ans;
    }
};

TEST_CASE("1929 - Concatenation of Array", "[Array]") {
    Solution s;
    SECTION("Example 1") {
        vector<int> nums{1, 2, 1};
        vector<int> ans{1, 2, 1, 1, 2, 1};
        REQUIRE(s.getConcatenation(nums) == ans);
    }
    SECTION("Example 2") {
        vector<int> nums{1, 3, 2, 1};
        vector<int> ans{1, 3, 2, 1, 1, 3, 2, 1};
        REQUIRE(s.getConcatenation(nums) == ans);
    }
}