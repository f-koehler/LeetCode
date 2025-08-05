#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>

namespace P0647 {
    class Solution {
      public:
        int countSubstrings(const std::string &s) {
            int count = 0;
            const int length = s.size();

            for (int i = 0; i < length; ++i) {
                // find all odd length palindromes
                int left = i;
                int right = i;
                while ((left >= 0) && (right < length) &&
                       (s[left] == s[right])) {
                    --left;
                    ++right;
                    ++count;
                }

                // find all even length palindromes
                left = i;
                right = i + 1;
                while ((left >= 0) && (right < length) &&
                       (s[left] == s[right])) {
                    --left;
                    ++right;
                    ++count;
                }
            }
            return count;
        }

        int countSubstringsManacher(const std::string &original) {
            // Interesting O(N) algorithm for this problem:
            // https://cp-algorithms.com/string/manacher.html
            // https://algo.monster/liteproblems/647
            //
            // TODO(fk): spend some time understand and implement
            std::string modified;
            modified.reserve(original.size() * 2 + 3);

            // add sentinel for start of string
            modified.push_back('^');

            // pad all characters with # on either side (all palindromes are odd
            // length in this modified representation)
            modified.push_back('#');
            for (char c : original) {
                modified.push_back(c);
                modified.push_back('#');
            }

            // add sentinel for end of string
            modified.push_back('$');

            const int length = modified.length();
            std::vector<int> palindrome_lengths(length, 0);
            int right = 0;

            for (int i = 1; i < length; ++i) {
                if (right > i) {
                }
            }

            return 0;
        }
    };

    TEST_CASE("0647 - Palindromic Substrings",
              "[Two Pointers][String][Dynamic Programming]") {

        SECTION("Example 1") {
            // Input: s = "abc"
            // Output: 3
            Solution s;
            REQUIRE(s.countSubstrings("abc") == 3);
        }

        SECTION("Example 2") {
            // Input: s = "aaa"
            // Output: 6
            Solution s;
            REQUIRE(s.countSubstrings("aaa") == 6);
        }
    }
} // namespace P0647
