#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <unordered_map>
#include <vector>

namespace P0954 {
    class Solution {
      public:
        bool canReorderDoubled(const std::vector<int> &arr) {
            // compute the frequency of each number
            std::unordered_map<int, int> count;
            for (const int num : arr) {
                ++(count[num]);
            }

            if (count[0] % 2) {
                // each 0 has to be paired with another one
                return false;
            }

            // we have to check the number with increasing magnitude to prevent
            // pairing a number with a larger number that we actually should
            // pair with a smaller one
            std::vector<int> keys;
            keys.reserve(count.size());
            for (auto &elem : count) {
                keys.push_back(elem.first);
            }

            std::ranges::sort(keys, std::ranges::less{},
                              [](int num) { return std::abs(num); });

            // try to find violation of our pairing requirement
            for (const int num : keys) {
                // check if we can pair all occurrences of this number with its
                // double
                if (count[2 * num] < count[num]) {
                    return false;
                }

                // decrease the count of 2*num due to pairing with num
                count[2 * num] -= count[num];
            }

            return true;
        }
    };

    TEST_CASE("0954 - Array of Doubled Pairs",
              "[Array][Hash Table][Greedy][Sorting]") {

        SECTION("Example 1") {
            // Input: arr = [3,1,3,6]
            // Output: false
            Solution s;
            std::vector<int> input{3, 1, 3, 6};
            REQUIRE(!s.canReorderDoubled(input));
        }

        SECTION("Example 2") {
            // Input: arr = [2,1,2,6]
            // Output: false
            Solution s;
            std::vector<int> input{2, 1, 2, 6};
            REQUIRE(!s.canReorderDoubled(input));
        }

        SECTION("Example 3") {
            // Input: arr = [4,-2,2,-4]
            // Output: true
            Solution s;
            std::vector<int> input{4, -2, 2, -4};
            REQUIRE(s.canReorderDoubled(input));
        }
    }
} // namespace P0954
