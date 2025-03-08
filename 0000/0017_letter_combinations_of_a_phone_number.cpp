#include <algorithm>
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include <string>
#include <string_view>
#include <vector>

namespace P0017 {
    class Solution {
      private:
        static constexpr std::array<std::string_view, 10> LettersForNumber = {
            "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

        void build_all_combinations(const std::vector<std::size_t> &digits,
                                    std::string &current_string,
                                    std::vector<std::string> &combinations) {
            const std::size_t current_length = current_string.size();
            const std::size_t target_length = digits.size();

            // check if we have met the target length -> found a valid
            // combination
            if (current_length >= target_length) {
                combinations.push_back(current_string);
                return;
            }

            // go through all letters for the next digit
            const std::string_view &letters =
                LettersForNumber[digits[current_length]];
            for (char letter : letters) {
                // add new letter
                current_string.push_back(letter);

                // recursion build all combinations with the current string as
                // prefix
                build_all_combinations(digits, current_string, combinations);

                // remove newly added letter
                current_string.pop_back();
            }
        }

      public:
        std::vector<std::string> letterCombinations(const std::string &digits) {
            const std::size_t length = digits.length();

            std::vector<std::string> combinations;

            // nothing to do if digits is emptys
            if (length == 0) {
                return combinations;
            }

            // allocate a buffer that can fit all combinations
            combinations.reserve(std::lround(std::pow(4, length)));

            // convert digits to actual integers that can be used in the
            // LettersForNumber mapping tables
            std::vector<std::size_t> digits_int(digits.size(), 0);
            std::transform(digits.cbegin(), digits.cend(), digits_int.begin(),
                           [](char c) { return c - '0'; });

            std::string current_combination;
            current_combination.reserve(length);

            build_all_combinations(digits_int, current_combination,
                                   combinations);

            return combinations;
        }
    };

    TEST_CASE("0017 - Letter Combinations of a Phone Number",
              "[Hash Table][String][Backtracking]") {
        Solution s;

        SECTION("Example 1") {
            std::vector<std::string> result = s.letterCombinations("23");
            std::sort(result.begin(), result.end());
            REQUIRE(result == std::vector<std::string>{"ad", "ae", "af", "bd",
                                                       "be", "bf", "cd", "ce",
                                                       "cf"});
        }
        SECTION("Example 2") {
            std::vector<std::string> result = s.letterCombinations("");
            std::sort(result.begin(), result.end());
            REQUIRE(result == std::vector<std::string>{});
        }
        SECTION("Example 3") {
            std::vector<std::string> result = s.letterCombinations("2");
            std::sort(result.begin(), result.end());
            REQUIRE(result == std::vector<std::string>{"a", "b", "c"});
        }
    }

} // namespace P0017