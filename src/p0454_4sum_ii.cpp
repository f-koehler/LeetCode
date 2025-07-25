#include <catch2/catch_test_macros.hpp>
#include <unordered_map>
#include <vector>

namespace P0454 {
    class Solution {
      public:
        int fourSumCount(const std::vector<int> &nums1,
                         const std::vector<int> &nums2,
                         const std::vector<int> &nums3,
                         const std::vector<int> &nums4) {
            // store the number of ways we reach each possible sum of elements
            // from nums3 and nums4
            // complexity: O(n^2)
            std::unordered_map<int, int> combinations_34;
            combinations_34.reserve(nums3.size() * nums4.size());
            for (int a : nums3) {
                for (int b : nums4) {
                    int sum = a + b;
                    auto pos = combinations_34.find(sum);
                    if (pos == combinations_34.end()) {
                        // new sum, insert with count 1
                        combinations_34.insert({sum, 1});
                    } else {
                        // new way of reaching existing sum
                        ++(pos->second);
                    }
                }
            }

            // loop over all combinations of elements from nums1 and nums2
            // check if the required remainder is in combinations_34
            // complexity: O(n^2)
            std::size_t combinations = 0;
            for (int a : nums1) {
                for (int b : nums2) {
                    auto pos = combinations_34.find(-(a + b));
                    if (pos != combinations_34.end()) {
                        combinations += pos->second;
                    }
                }
            }
            return combinations;
        }
    };

    TEST_CASE("0454 - 4Sum II", "[Array][Hash Table]") {

        SECTION("Example 1") {
            // Input: nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 =
            // [0,2] Output: 2
            Solution s;
            REQUIRE(s.fourSumCount({1, 2}, {-2, -1}, {-1, 2}, {0, 2}) == 2);
        }

        SECTION("Example 2") {
            // Input: nums1 = [0], nums2 = [0], nums3 = [0], nums4 = [0]
            // Output: 1
            Solution s;
            REQUIRE(s.fourSumCount({0}, {0}, {0}, {0}) == 1);
        }

        SECTION("Example 3") {
            Solution s;
            REQUIRE(s.fourSumCount({-1, -1}, {-1, 1}, {-1, 1}, {1, -1}) == 6);
        }
    }
} // namespace P0454
