#include <catch2/catch_test_macros.hpp>

class Solution {
  public:
    bool isPalindrome(int x) {
        // negative number cannot be palindrome
        if (x < 0) {
            return false;
        }

        // 0...9 are palindrome
        if (x < 10) {
            return true;
        }

        // number ending with 0 cannot be palindrome
        if (x % 10 == 0) {
            return false;
        }

        int rev = 0;
        while (rev < x) {
            rev = rev * 10 + x % 10;
            x /= 10;
        }

        // if rev is equal to the remainder, we found a palindrome
        // the input was of even length
        // and the reversed last half is equal to the first half
        if (rev == x) {
            return true;
        }

        // handle the case that the input was of odd length
        // the middle number does not matter
        rev /= 10;
        if (rev == x) {
            return true;
        }

        return false;
    }
};

TEST_CASE("0009 - Palindrome Number", "[math]") {
    REQUIRE(Solution().isPalindrome(121) == true);
    REQUIRE(Solution().isPalindrome(-121) == false);
    REQUIRE(Solution().isPalindrome(10) == false);
}