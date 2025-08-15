#include <bit>
#include <catch2/catch_test_macros.hpp>

namespace P0231 {
    class Solution {
      public:
        constexpr bool isPowerOfTwo(int n) {
            return (n > 0) && ((n & (n - 1)) == 0);
        }

        constexpr bool isPowerOfTwoPopcount(int n) {
            return (n > 0) &&
                   (std::popcount(static_cast<unsigned int>(n)) == 1);
        }
    };

    TEST_CASE("0231 - Power of Two", "[Math][Bit Manipulation][Recursion]") {

        SECTION("Example 1") {
            // Input: n = 1
            // Output: true
            Solution s;
            REQUIRE(s.isPowerOfTwo(1));
            REQUIRE(s.isPowerOfTwoPopcount(1));
        }

        SECTION("Example 2") {
            // Input: n = 16
            // Output: true
            Solution s;
            REQUIRE(s.isPowerOfTwo(16));
            REQUIRE(s.isPowerOfTwoPopcount(16));
        }

        SECTION("Example 3") {
            // Input: n = 3
            // Output: false
            Solution s;
            REQUIRE(!s.isPowerOfTwo(3));
            REQUIRE(!s.isPowerOfTwoPopcount(3));
        }
    }
} // namespace P0231
