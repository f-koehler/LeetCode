#include <catch2/catch_test_macros.hpp>
#include <string>

namespace P2390 {
    class Solution {
      public:
        std::string removeStars(const std::string &s) {
            std::string character_stack;
            character_stack.reserve(s.size());
            for (char c : s) {
                if (c == '*') {
                    // instructions say that stack will not be empty
                    assert(!character_stack.empty());
                    character_stack.pop_back();
                    continue;
                }
                character_stack.push_back(c);
            }
            return character_stack;
        }
    };

    TEST_CASE("2390 - Removing Stars From a String",
              "[String][Stack][Simulation]") {

        SECTION("Example 1") {
            // Input: s = "leet**cod*e"
            // Output: "lecoe"
            Solution s;
            REQUIRE(s.removeStars("leet**cod*e") == "lecoe");
        }

        SECTION("Example 2") {
            // Input: s = "erase*****"
            // Output: ""
            Solution s;
            REQUIRE(s.removeStars("erase*****") == "");
        }
    }
} // namespace P2390
