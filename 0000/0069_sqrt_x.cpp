#include <catch2/catch_test_macros.hpp>

class Solution {
  public:
    inline constexpr int mySqrt(int x) {
        if (x == 0) {
            return 0;
        }
        if (x <= 3) {
            return 1;
        }
        int min = 2;
        int max = x / 2 + 1; // sqrt(x) < x/2 for all x>3
        while (min < max) {
            const int center = (min + max) / 2;
            // to prevent 32bit overflow we cannot use center*center > x but
            // instead divide x by center
            if (center > x / center) {
                max = center;
            } else {
                min = center + 1;
            }
        }
        return min - 1;
    }
};

TEST_CASE("0069 - Sqrt(x)", "[Math][Binary Search]") {
    Solution s;
    SECTION("Example 1") {
        // cppcheck-suppress knownConditionTrueFalse
        REQUIRE(s.mySqrt(4) == 2);
    }
    SECTION("Example 2") {
        // cppcheck-suppress knownConditionTrueFalse
        REQUIRE(s.mySqrt(8) == 2);
    }
    SECTION("Example 3") {
        // cppcheck-suppress knownConditionTrueFalse
        REQUIRE(s.mySqrt(2147395599) == 46339);
    }
    SECTION("Additional Cases") {
        // cppcheck-suppress knownConditionTrueFalse
        REQUIRE(s.mySqrt(0) == 0);
        // cppcheck-suppress knownConditionTrueFalse
        REQUIRE(s.mySqrt(1) == 1);
        // cppcheck-suppress knownConditionTrueFalse
        REQUIRE(s.mySqrt(2) == 1);
        // cppcheck-suppress knownConditionTrueFalse
        REQUIRE(s.mySqrt(3) == 1);
    }
}