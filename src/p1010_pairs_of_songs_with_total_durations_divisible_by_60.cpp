#include <algorithm>
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <vector>

namespace P1010 {
    class Solution {
      public:
        int numPairsDivisibleBy60(std::vector<int> &time) {
            // (a+b) mod 60 == (a mod 60) + (b mod 60)

            // step 1: take all times module 60
            // complexity: O(n)
            std::transform(time.begin(), time.end(), time.begin(),
                           [](int t) { return t % 60; });

            // step 2: compute the frequency of all possible remainders
            // complexity: O(n)
            // important to use uint64_t here to prevent overflows during
            // products in step 3 & 4
            std::array<uint64_t, 60> remainder_count{0};
            std::for_each(time.begin(), time.end(),
                          [&remainder_count](int remainder) {
                              ++remainder_count[remainder];
                          });

            // step 3: iterate through all remainder_couts from 1 to 29
            // compute the combinations by multiplying with the count for what
            // is missing to get 60s complexity: O(n)
            std::size_t combinations = 0;
            for (std::size_t remainder = 1; remainder < 30; ++remainder) {
                combinations += remainder_count[remainder] *
                                remainder_count[60 - remainder];
            }

            // step 4: handle special cases: both times have remainder 0 or both
            // times have remainder 30
            //
            // N (N-1) /2 to prevent double counts
            combinations += (remainder_count[0] * (remainder_count[0] - 1)) / 2;
            combinations +=
                (remainder_count[30] * (remainder_count[30] - 1)) / 2;

            return combinations;
        }
    };

    TEST_CASE("1010 - Pairs of Songs With Total Durations Divisible by 60",
              "[Array][Hash Table][Counting]") {

        SECTION("Example 1") {
            // Input: time = [30,20,150,100,40]
            // Output: 3
            Solution s;
            std::vector<int> input{30, 20, 150, 100, 40};
            REQUIRE(s.numPairsDivisibleBy60(input) == 3);
        }

        SECTION("Example 2") {
            // Input: time = [60,60,60]
            // Output: 3
            Solution s;
            std::vector<int> input{60, 60, 60};
            REQUIRE(s.numPairsDivisibleBy60(input) == 3);
        }
    }
} // namespace P1010
