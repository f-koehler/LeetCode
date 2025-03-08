#include <catch2/catch_test_macros.hpp>
#include <iterator>
#include <string>

namespace P0345 {
    inline bool is_vowel(char c) {
        switch (c) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
            return true;
        default:
            return false;
        }
    }

    class Solution {
      public:
        std::string reverseVowels(const std::string &s) {
            std::string result(s);
            auto left = result.begin();
            auto right = std::prev(result.end());
            bool left_is_vowel = is_vowel(*left);
            bool right_is_vowel = is_vowel(*right);
            while (left < right) {
                if (!left_is_vowel) {
                    ++left;
                    left_is_vowel = is_vowel(*left);
                    continue;
                }
                if (!right_is_vowel) {
                    --right;
                    right_is_vowel = is_vowel(*right);
                    continue;
                }

                std::swap(*left, *right);
                ++left;
                --right;
                left_is_vowel = is_vowel(*left);
                right_is_vowel = is_vowel(*right);
            }
            return result;
        }
    };

    TEST_CASE("0345 - Reverse Vowels of a String", "[Two Pointers][String]") {
        Solution s;
        SECTION("Example 1") {
            REQUIRE(s.reverseVowels("IceCreAm") == "AceCreIm");
        }
        SECTION("Example 2") {
            REQUIRE(s.reverseVowels("leetcode") == "leotcede");
        }
    }
} // namespace P0345