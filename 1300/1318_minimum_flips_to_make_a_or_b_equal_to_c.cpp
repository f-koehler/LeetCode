#include <bitset>
#include <catch2/catch_test_macros.hpp>
#include <iostream>

namespace P1318 {
    class Solution {
      public:
        int minFlips(int a, int b, int c) {
            int flips = 0;
            while (a || b || c) {
                const int bit_a = a & 1;
                const int bit_b = b & 1;
                const int bit_c = c & 1;
                if (bit_c) {
                    // c_i == 1: add one flip if both a_i and b_i are 0
                    flips += (~(bit_a | bit_b)) & 1;
                } else {
                    // c_i ==0: flip a if one, flip b if one, resulting in 0, 1,
                    // or 2 flips
                    flips += bit_a + bit_b;
                }
                a >>= 1;
                b >>= 1;
                c >>= 1;
            }
            return flips;
        }
    };

    TEST_CASE("1318 - Minimum Flips To Make a OR b Equal to c",
              "[Bit Manipulation]") {
        Solution s;
        SECTION("Example 1") { REQUIRE(s.minFlips(2, 6, 5) == 3); }
        SECTION("Example 2") { REQUIRE(s.minFlips(4, 2, 7) == 1); }
        SECTION("Example 3") { REQUIRE(s.minFlips(1, 2, 3) == 0); }
        SECTION("Single Bit Tests") {
            REQUIRE(s.minFlips(0, 0, 0) == 0);
            REQUIRE(s.minFlips(0, 0, 1) == 1);
            REQUIRE(s.minFlips(0, 1, 0) == 1);
            REQUIRE(s.minFlips(0, 1, 1) == 0);
            REQUIRE(s.minFlips(1, 0, 0) == 1);
            REQUIRE(s.minFlips(1, 0, 1) == 0);
            REQUIRE(s.minFlips(1, 1, 0) == 2);
            REQUIRE(s.minFlips(1, 1, 1) == 0);
        }
    }
} // namespace P1318
