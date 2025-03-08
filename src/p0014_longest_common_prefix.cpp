#include <algorithm>
#include <cassert>
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>

namespace P0014 {
    class Solution {
      public:
        std::string longestCommonPrefix(const std::vector<std::string> &strs) {
            assert(!strs.empty());
            const std::size_t num_strings = strs.size();
            if (num_strings == 1) {
                return strs[0];
            }
            const std::size_t len =
                std::min_element(
                    strs.cbegin(), strs.cend(),
                    [](const std::string &a, const std::string &b) {
                        return a.length() < b.length();
                    })
                    ->length();

            for (std::size_t i = 0; i < len; ++i) {
                for (std::size_t j = 1; j < num_strings; ++j) {
                    if (strs[j][i] != strs[0][i]) {
                        return strs[0].substr(0, i);
                    }
                }
            }
            return strs[0].substr(0, len);
        }
    };

    TEST_CASE("0014 - Longest Common Prefix", "[String][Trie]") {

        SECTION("Example 1") {
            // Input: strs = ["flower","flow","flight"]
            // Output: "fl"
            Solution s;
            REQUIRE(s.longestCommonPrefix({"flower", "flow", "flight"}) ==
                    "fl");
        }

        SECTION("Example 2") {
            // Input: strs = ["dog","racecar","car"]
            // Output: ""
            Solution s;
            REQUIRE(s.longestCommonPrefix({"dog", "racecar", "car"}) == "");
        }
    }
} // namespace P0014