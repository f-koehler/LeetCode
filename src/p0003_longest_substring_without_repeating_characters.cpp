#include <cassert>
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <unordered_map>

namespace P0003 {
    class Solution {
      public:
        int lengthOfLongestSubstring(const std::string &s) {
            const std::size_t length = s.size();
            assert(length >= 0);
            assert(length <= 50000);

            if (s.empty()) {
                return 0;
            }

            std::size_t max_length = 1;
            std::size_t start = 0;
            std::unordered_map<char, std::size_t> current_characters;
            current_characters.insert({s.front(), 0});

            for (std::size_t index = 1; index < length; ++index) {
                const char new_character = s[index];
                const auto duplicate = current_characters.find(new_character);
                if (duplicate != current_characters.end()) {
                    // the current subsequence has ended
                    max_length = std::max(max_length, index - start);

                    // remove characters up to and including the duplicate
                    const std::size_t duplicate_index = duplicate->second;
                    for (std::size_t remove_index = start;
                         remove_index <= duplicate_index; ++remove_index) {
                        current_characters.erase(s[remove_index]);
                    }

                    // start new sequence
                    start = duplicate_index + 1;
                }

                current_characters.insert({new_character, index});
            }

            // handle the subsequence ending at the end of the string
            max_length = std::max(max_length, length - start);

            return max_length;
        }
    };

    TEST_CASE("0003 - Longest Substring Without Repeating Characters",
              "[Hash Table][String][Sliding Window]") {

        SECTION("Example 1") {
            // Input: s = "abcabcbb"
            // Output: 3
            Solution s;
            REQUIRE(s.lengthOfLongestSubstring("abcabcbb") == 3);
        }

        SECTION("Example 2") {
            // Input: s = "bbbbb"
            // Output: 1
            Solution s;
            REQUIRE(s.lengthOfLongestSubstring("bbbbb") == 1);
        }

        SECTION("Example 3") {
            // Input: s = "pwwkew"
            // Output: 3
            Solution s;
            REQUIRE(s.lengthOfLongestSubstring("pwwkew") == 3);
        }
    }
} // namespace P0003
