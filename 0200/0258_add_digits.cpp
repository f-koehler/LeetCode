#include <catch2/catch_test_macros.hpp>

class Solution {
  public:
    /*
     * The idea is to look at all possible outcomes:
     *
     * 0: can only be reached from 0
     * 1: can only be reached from 1
     * 2: can only be reached from 2 and 11, i.e. for n with n % 9==2
     * 3: can only be reached from 3, 12, 21, and 111, i.e. for n with n % 9==3
     * 4: can only be reached from 4, 13, 31, 22, 211, 121, 112, and 1111, i.e.
     * for n with n % 9==4
     *
     * ...
     *
     * Exception are numbers divisible by 9:
     * 9 -> 9
     * 18 -> 9
     * 27 -> 9
     *
     * So we can summarize:
     * n==0 -> 0
     * n>0, n%9==0 -> 9
     * n>0, n%9!=0 -> n%9
     *
     * This can be further simplified to:
     * n==0 -> 0
     * n!=0 -> 1+(n-1) mod 9
     *
     * In C (but not in Python!!!) we can exploit -1%9==-1 to optimize to
     * n!=0 -> 1+(n-1) mod 9
     */
    inline constexpr int addDigits(int num) {
        // In Python -1 % 9 == 8 -> handle separately
        return 1 + (num - 1) % 9;
    }
};

TEST_CASE("0258 - Add Digits", "[Math][Simulation][Number Theory]") {
    Solution s;
    SECTION("Example 1") {
        // cppcheck-suppress knownConditionTrueFalse
        REQUIRE(s.addDigits(38) == 2);
    }
    SECTION("Example 2") {
        // cppcheck-suppress knownConditionTrueFalse
        REQUIRE(s.addDigits(0) == 0);
    }
    SECTION("Example 3") {
        // cppcheck-suppress knownConditionTrueFalse
        REQUIRE(s.addDigits(18) == 9);
    }
}