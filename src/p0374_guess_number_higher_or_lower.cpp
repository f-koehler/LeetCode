#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include <vector>

namespace P0374 {

    // volatile is important to prevent inlining of the guess function
    thread_local static volatile int pick = 6;

    /**
     * Forward declaration of guess API.
     * @param  num   your guess
     * @return 	     -1 if num is higher than the picked number
     *			      1 if num is lower than the picked number
     *               otherwise return 0
     * int guess(int num);
     */
    int guess(int num) {
        if (num == pick) {
            return 0;
        }
        if (num > pick) {
            return -1;
        }
        return 1;
    }

    class Solution {
      public:
        int guessNumber(int n) {
            int low = 1;
            int high = n;

            while (low < high) {
                const int my_guess = low + (high - low) / 2;
                switch (guess(my_guess)) {
                case -1:
                    // pick is smaller than guess
                    high = my_guess;
                    continue;
                case 1:
                    // pick is larger than guess
                    // +1 is important as integer division is rounding down and
                    // we can get stuck in an infinite loop e.g.: n=2, pick =2
                    low = my_guess + 1;
                    continue;
                default:
                    return my_guess;
                }
            }
            return low;
        }
    };

    TEST_CASE("0374 - Guess Number Higher or Lower",
              "[Binary Search][Interactive]") {

        SECTION("Example 1") {
            // Input: n = 10, pick = 6
            // Output: 6
            Solution s;
            pick = 6;
            REQUIRE(s.guessNumber(10) == 6);
        }

        SECTION("Example 2") {
            // Input: n = 1, pick = 1
            // Output: 1
            Solution s;
            pick = 1;
            REQUIRE(s.guessNumber(1) == 1);
        }

        SECTION("Example 3") {
            // Input: n = 2, pick = 1
            // Output: 1
            Solution s;
            pick = 1;
            REQUIRE(s.guessNumber(2) == 1);
        }
    }
} // namespace P0374
