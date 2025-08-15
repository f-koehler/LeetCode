#include <catch2/catch_test_macros.hpp>

namespace P0342 {
    class Solution {
      public:
        constexpr bool isPowerOfFour(int n) {
            // countr_zero() % 2 == 0 check ensures that the number of zeros
            // after the one is even
            //
            // every second power of two is a power of four, so the number of
            // zeros must be even
            //
            // we can also check this using the bit mask 0b...0101010101 =
            // 0x..5555 but this would be more cumbersome
            return (n > 0) &&
                   (std::popcount(static_cast<unsigned int>(n)) == 1) &&
                   (std::countr_zero(static_cast<unsigned int>(n)) % 2 == 0);
        }
    };

    TEST_CASE("0342 - Power of Four", "[Math][Bit Manipulation][Recursion]") {

        SECTION("Example 1") {
            // Input: n = 16
            // Output: true
            Solution s;
            REQUIRE(s.isPowerOfFour(16));
        }

        SECTION("Example 2") {
            // Input: n = 5
            // Output: false
            Solution s;
            REQUIRE(!s.isPowerOfFour(5));
        }

        SECTION("Example 3") {
            // Input: n = 1
            // Output: true
            Solution s;
            REQUIRE(s.isPowerOfFour(1));
        }
        SECTION("Example 4") {
            // Input: n = 8
            // Output: false
            Solution s;
            REQUIRE(!s.isPowerOfFour(8));
        }
    }
} // namespace P0342
