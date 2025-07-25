#include <algorithm>
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P0923 {
    static constexpr std::size_t Modulo = 1'000'000'007;

    class Solution {
      public:
        int threeSumMulti(const std::vector<int> &arr, int target) {
            // exploit the small number range and compute frequency of each
            // element
            std::array<std::size_t, 101> num_freq{0};
            std::for_each(arr.cbegin(), arr.cend(),
                          [&num_freq](int num) { ++num_freq[num]; });

            const std::size_t num_elements = arr.size();
            std::size_t num_combinations = 0;

            // loop for second element of triplet
            for (std::size_t j = 0; j < num_elements; ++j) {
                const int second = arr[j];

                // decrement count as current element is part of the triplet
                // it will be consumed by all triplets that have this second
                // element
                //
                // if a number occurs multiple times, we will count the triplet
                // multiple times as intended
                --num_freq[second];

                // loop for first element of triplet
                for (std::size_t i = 0; i < j; ++i) {
                    const int first = arr[i];
                    const int third = target - first - second;

                    if ((third < 0) || (third > 100)) {
                        // ignore if third element is out of valid range
                        continue;
                    }

                    num_combinations =
                        (num_combinations + num_freq[third]) % Modulo;
                }
            }

            return num_combinations;
        }
    };

    TEST_CASE("0923 - 3Sum With Multiplicity",
              "[Array][Hash Table][Two Pointers][Sorting][Counting]") {

        SECTION("Example 1") {
            // Input: arr = [1,1,2,2,3,3,4,4,5,5], target = 8
            // Output: 20
            Solution s;
            REQUIRE(s.threeSumMulti({1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, 8) == 20);
        }

        SECTION("Example 2") {
            // Input: arr = [1,1,2,2,2,2], target = 5
            // Output: 12
            Solution s;
            REQUIRE(s.threeSumMulti({1, 1, 2, 2, 2, 2}, 5) == 12);
        }

        SECTION("Example 3") {
            // Input: arr = [2,1,3], target = 6
            // Output: 1
            Solution s;
            REQUIRE(s.threeSumMulti({2, 1, 3}, 6) == 1);
        }
    }
} // namespace P0923
