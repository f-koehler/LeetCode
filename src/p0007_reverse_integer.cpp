#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <limits>

namespace LeetCode::P0007 {
    class Solution {
      public:
        [[nodiscard]] static constexpr int32_t reverse(int32_t x) noexcept {
            static constexpr auto overflow_threshold = std::numeric_limits<int32_t>::max() / 10;
            static constexpr auto underflow_threshold = std::numeric_limits<int32_t>::min() / 10;

            int32_t result = 0;
            while (x != 0) {
                const int32_t digit = x % 10;
                x /= 10;

                // check if we overflow/underflow by multiplying by 10
                if(result > overflow_threshold) { return 0; }
                if(result < underflow_threshold) { return 0; }

                // check if we overflow/underflow by adding the new digit after multiplying with 10
                // overflow_threshold * 10 = 2147483640
                // largest int32_t = 2147483647 -> we can squeeze a 7 or smaller as the last digit
                //
                // underflow_threshold * 10 = -2147483650
                // smallest in32_t = -2147483648 -> last digit is aceptable if 8 or smaller
                if((result == overflow_threshold) && (digit > 7)) { return 0;}
                if((result == underflow_threshold) && (digit < -8)) { return 0;}

                result = result * 10 + digit;
            }
            return result;
        }
    };

    TEST_CASE("0007 - Reverse Integer", "[Math]") {

        SECTION("Example 1") {
            // Input: x = 123
            // Output: 321
            REQUIRE(Solution::reverse(123) == 321);
        }

        SECTION("Example 2") {
            // Input: x = -123
            // Output: -321
            REQUIRE(Solution::reverse(-123) == -321);
        }

        SECTION("Example 3") {
            // Input: x = 120
            // Output: 21
            REQUIRE(Solution::reverse(120) == 21);
        }

        SECTION("Overflow positive") {
            // 1000000003 reversed = 3000000001 > INT32_MAX
            REQUIRE(Solution::reverse(1000000003) == 0);
        }

        SECTION("Overflow negative") {
            // -1000000003 reversed = -3000000001 < INT32_MIN
            REQUIRE(Solution::reverse(-1000000003) == 0);
        }

        SECTION("int32_t min") {
            // -2147483648 reversed = -8463847412, way out of range
            REQUIRE(Solution::reverse(INT32_MIN) == 0);
        }

        SECTION("int32_t max") {
            // 2147483647 reversed = 7463847412, way out of range
            REQUIRE(Solution::reverse(INT32_MAX) == 0);
        }

        SECTION("Zero") {
            REQUIRE(Solution::reverse(0) == 0);
        }
    }
} // namespace LeetCode::P0007
