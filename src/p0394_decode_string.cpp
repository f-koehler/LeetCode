#include <catch2/catch_test_macros.hpp>
#include <cctype>
#include <deque>
#include <string>

namespace P0394 {
    class Solution {
      private:
        std::string repeat_string(std::size_t repetitions,
                                  const std::string &str) {
            std::string result;
            result.reserve(str.size() * repetitions);
            for (std::size_t i = 0; i < repetitions; ++i) {
                result += str;
            }
            return result;
        }

      public:
        std::string decodeString(const std::string &s) {
            std::deque<std::pair<std::size_t, std::string>> stack;
            std::size_t num_repetitions = 0UL;
            std::string current_string;
            current_string.reserve(500'000UL);
            for (auto c : s) {
                // encountered digit, update num_repetitions
                if (std::isdigit(c)) {
                    num_repetitions = num_repetitions * 10UL +
                                      static_cast<std::size_t>(c - '0');
                    continue;
                }
                // encountered open bracket -> start new string and count
                // store current string and repetitions (of the string that is
                // now starting!!!) on the stack
                if (c == '[') {
                    stack.emplace_back(num_repetitions, current_string);
                    num_repetitions = 0UL;
                    current_string.clear();
                    continue;
                }

                // encountered closing bracket -> fetch previous string and the
                // number of repetitions for the current string from the stack
                if (c == ']') {
                    const auto [reps, previous_string] = stack.back();
                    stack.pop_back();
                    current_string =
                        previous_string + repeat_string(reps, current_string);
                    continue;
                }

                // normal character, just append to current string
                current_string += c;
            }
            return current_string;
        }
    };

    TEST_CASE("0394 - Decode String", "[String][Stack][Recursion]") {

        SECTION("Example 1") {
            // Input: s = "3[a]2[bc]"
            // Output: "aaabcbc"
            Solution s;
            REQUIRE(s.decodeString("3[a]2[bc]") == "aaabcbc");
        }

        SECTION("Example 2") {
            // Input: s = "3[a2[c]]"
            // Output: "accaccacc"
            Solution s;
            REQUIRE(s.decodeString("3[a2[c]]") == "accaccacc");
        }

        SECTION("Example 3") {
            // Input: s = "2[abc]3[cd]ef"
            // Output: "abcabccdcdcdef"
            Solution s;
            REQUIRE(s.decodeString("2[abc]3[cd]ef") == "abcabccdcdcdef");
        }
    }
} // namespace P0394
