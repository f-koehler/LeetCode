#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <string>

namespace P1456 {
    constexpr inline bool is_vowel(char c) {
        return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
    }
    class Solution {
      public:
        int maxVowels(const std::string &s, const int &k) {
            int num_vowels =
                std::count_if(s.cbegin(), s.cbegin() + k, is_vowel);
            int max_vowels = num_vowels;

            for (std::size_t i = 0, j = k; j < s.size(); ++i, ++j) {
                if (is_vowel(s[i])) {
                    --num_vowels;
                }
                if (is_vowel(s[j])) {
                    ++num_vowels;
                }
                max_vowels = std::max(max_vowels, num_vowels);
            }
            return max_vowels;
        }
    };

    TEST_CASE("1456 - Maximum Number of Vowels in a Substring of Given Length",
              "[String][Sliding Window]") {

        SECTION("Example 1") {
            // Input: s = "abciiidef", k = 3
            // Output: 3
            Solution s;
            REQUIRE(s.maxVowels("abciiidef", 3) == 3);
        }

        SECTION("Example 2") {
            // Input: s = "aeiou", k = 2
            // Output: 2
            Solution s;
            REQUIRE(s.maxVowels("aeiou", 2) == 2);
        }

        SECTION("Example 3") {
            // Input: s = "leetcode", k = 3
            // Output: 2
            Solution s;
            REQUIRE(s.maxVowels("leetcode", 3) == 2);
        }
    }
} // namespace P1456