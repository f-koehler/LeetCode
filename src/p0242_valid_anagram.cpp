#include <array>
#include <catch2/catch_test_macros.hpp>
#include <string>

namespace P0242 {
    class Solution {
      public:
        [[nodiscard]] bool isAnagram(const std::string &s,
                                     const std::string &t) noexcept {
            if (s.size() != t.size()) {
                return false;
            }
            // follow-up: by replacing this with a std::unordered_map<char, int>
            // we could extend it beyond lower-case ASCII characters
            std::array<int, 26> count{0};
            for (const char c : s) {
                ++count[c - 'a'];
            }
            for (const char c : t) {
                if (--count[c - 'a'] < 0) {
                    return false;
                }
            }
            return true;
        }
    };

    TEST_CASE("0242 - Valid Anagram", "[Hash Table][String][Sorting][NeetCode150]") {
        SECTION("Example 1") {
            Solution s;
            REQUIRE(s.isAnagram("anagram", "nagaram"));
        }
        SECTION("Example 2") {
            Solution s;
            REQUIRE(!s.isAnagram("rat", "car"));
        }
        SECTION("Example 3") {
            Solution s;
            REQUIRE(!s.isAnagram("ab", "a"));
        }
    }
} // namespace P0242