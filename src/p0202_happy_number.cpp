#include <catch2/catch_test_macros.hpp>

namespace P0202 {
    class Solution {
      public:
        [[nodiscard]] constexpr int getSquareOfDigits(int n) noexcept {
            int sum = 0;
            while (n > 0) {
                const int digit = n % 10;
                sum += (digit * digit);
                n /= 10;
            }
            return sum;
        }

        [[nodiscard]] bool isHappyFloyd(const int n) noexcept {
            // we know that n>0
            if (n == 1) {
                return true;
            }

            // Use Floyd's Cycle detection algorithm (tortoise and hare)
            int slow = n;
            int fast = getSquareOfDigits(n);
            while (slow != fast) {
                slow = getSquareOfDigits(slow);
                fast = getSquareOfDigits(getSquareOfDigits(fast));
            }
            return fast == 1;
        }
    };

    TEST_CASE("0202 - Happy Number",
              "[Hash Table][Math][Two Pointers][NeetCode150]") {

        SECTION("Example 1") {
            // Input: n = 19
            // Output: true
            Solution s;
            REQUIRE(s.isHappyFloyd(19));
        }

        SECTION("Example 2") {
            // Input: n = 2
            // Output: false
            Solution s;
            REQUIRE(!s.isHappyFloyd(2));
        }
    }
} // namespace P0202