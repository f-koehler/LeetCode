#include <catch2/catch_test_macros.hpp>
#include <numeric>
#include <string>

namespace P1071 {
    // Euclidean algorithm to compute gcd.
    template <typename T>
    T gcd(T a, T b) {
        T t;
        while (b != 0) {
            t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    class Solution {
      public:
        std::string gcdOfStrings(const std::string &str1,
                                 const std::string &str2) {
            // Check if the we get the same string independent of concatenation
            // order. If we don't, they cannot be the product of a common gcd.
            if (str1 + str2 != str2 + str1) {
                return "";
            }

            // Compute the gcd of the string lengths, this will be the length of
            // the gcd string.
            const std::size_t gcd_length = std::gcd(str1.size(), str2.size());

            return str1.substr(0, gcd_length);
        }
        std::string gcdOfStringsCustomGCD(const std::string &str1,
                                          const std::string &str2) {
            // Check if the we get the same string independent of concatenation
            // order. If we don't, they cannot be the product of a common gcd.
            if (str1 + str2 != str2 + str1) {
                return "";
            }

            // Compute the gcd of the string lengths, this will be the length of
            // the gcd string.
            const std::size_t gcd_length = gcd(str1.size(), str2.size());

            return str1.substr(0, gcd_length);
        }
    };

    TEST_CASE("1071 - Greatest Common Divisor of Strings", "[Math][String]") {
        Solution s;
        SECTION("Example 1") {
            REQUIRE(s.gcdOfStrings("ABCABC", "ABC") == "ABC");
            REQUIRE(s.gcdOfStringsCustomGCD("ABCABC", "ABC") == "ABC");
        }
        SECTION("Example 2") {
            REQUIRE(s.gcdOfStrings("ABABAB", "ABAB") == "AB");
            REQUIRE(s.gcdOfStringsCustomGCD("ABABAB", "ABAB") == "AB");
        }
        SECTION("Example 3") {
            REQUIRE(s.gcdOfStrings("LEET", "CODE") == "");
            REQUIRE(s.gcdOfStringsCustomGCD("LEET", "CODE") == "");
        }
    }
} // namespace P1071
