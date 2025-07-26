#include <array>
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>

namespace P2131 {
    class Solution {
      public:
        int longestPalindrome(const std::vector<std::string> &words) {
            std::size_t length = 0;

            // store the available words
            std::array<std::array<std::size_t, 26>, 26> count{
                std::array<std::size_t, 26>{0}};

            // build the largest palindrome using pairs of words
            for (const std::string &word : words) {
                int i = word[0] - 'a';
                int j = word[1] - 'a';
                if (count[j][i] > 0) {
                    // we already found the same word with the letters flipped
                    //
                    // we use the pair for our palindrome
                    length += 4;
                    --(count[j][i]);
                } else {
                    // we found an unpaired (for now) word, store it for later
                    // use
                    ++(count[i][j]);
                }
            }

            // check if we have word left over that is itself a palindrome
            //
            // if yes, we could add it to the middle of our palindrome that is
            // build from word pairs for now
            //
            // we do this now because we can get a larger length using pairs of
            // palindromic words in the loop above
            //
            // only if we have left over words that are palindromes themselves,
            // we add one in the middle
            //
            // of course we can only do this with one word
            for (int i = 0; i < 26; ++i) {
                if (count[i][i] > 0) {
                    return length + 2;
                }
            }

            // if we have no such word left we return the palindrome length
            // as-is
            return length;
        }
    };

    TEST_CASE("2131 - Longest Palindrome by Concatenating Two Letter Words",
              "[Array][Hash Table][String][Greedy][Counting]") {

        SECTION("Example 1") {
            // Input: words = ["lc","cl","gg"]
            // Output: 6
            Solution s;
            REQUIRE(s.longestPalindrome(
                        std::vector<std::string>{"lc", "cl", "gg"}) == 6);
        }

        SECTION("Example 2") {
            // Input: words = ["ab","ty","yt","lc","cl","ab"]
            // Output: 8
            Solution s;
            REQUIRE(s.longestPalindrome({"ab", "ty", "yt", "lc", "cl", "ab"}) ==
                    8);
        }

        SECTION("Example 3") {
            // Input: words = ["cc","ll","xx"]
            // Output: 2
            Solution s;
            REQUIRE(s.longestPalindrome({"cc", "ll", "xx"}) == 2);
        }
    }
} // namespace P2131
