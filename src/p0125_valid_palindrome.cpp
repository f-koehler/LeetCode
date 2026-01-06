#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <cctype>
#include <ranges>
#include <string>

namespace P0125 {
    class Solution {
      public:
        [[nodiscard]] std::string sanitize(std::string s) const {
            std::locale loc("C");
            return s | std::views::filter([&loc](char c) {
                       return std::isalnum(c, loc);
                   }) |
                   std::views::transform(
                       [&loc](char c) { return std::tolower(c, loc); }) |
                   std::ranges::to<std::string>();
        }

        [[nodiscard]] bool isPalindrome(const std::string s) const {
            const std::string sanitized = sanitize(s);
            if (sanitized.size() < 2) {
                return true;
            }

            // we do not need to check the central character for odd-length
            // strings, as it will naturally match itself
            const auto half_length = s.size() / 2;

            return std::ranges::equal(sanitized | std::views::take(half_length),
                                      sanitized | std::views::reverse |
                                          std::views::take(half_length));
        }
    };

    TEST_CASE("0125 - Valid Palindrome", "[Two Pointers][String]") {

        SECTION("Sanitize") {
            SECTION("Example 1") {
                // Input: s = "A man, a plan, a canal: Panama"
                // Output: true
                Solution s;
                REQUIRE(s.sanitize("A man, a plan, a canal: Panama") ==
                        "amanaplanacanalpanama");
            }

            SECTION("Example 2") {
                // Input: s = "race a car"
                // Output: false
                Solution s;
                REQUIRE(s.sanitize("race a car") == "raceacar");
            }

            SECTION("Example 3") {
                // Input: s = " "
                // Output: true
                Solution s;
                REQUIRE(s.sanitize(" ") == "");
            }
        }

        SECTION("Example 1") {
            // Input: s = "A man, a plan, a canal: Panama"
            // Output: true
            Solution s;
            REQUIRE(s.isPalindrome("A man, a plan, a canal: Panama"));
        }

        SECTION("Example 2") {
            // Input: s = "race a car"
            // Output: false
            Solution s;
            REQUIRE(!s.isPalindrome("race a car"));
        }

        SECTION("Example 3") {
            // Input: s = " "
            // Output: true
            Solution s;
            REQUIRE(s.isPalindrome(" "));
        }
    }
} // namespace P0125