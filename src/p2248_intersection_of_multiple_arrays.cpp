#include <array>
#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P2248 {
    class Solution {
      public:
        std::vector<int>
        intersection(const std::vector<std::vector<int>> &nums) {
            const int num_sets = nums.size();

            std::array<int, 1001> count;
            count.fill(0);
            for (const std::vector<int> &set : nums) {
                for (const int num : set) {
                    ++count[num];
                }
            }

            std::vector<int> result;
            result.reserve(1000);
            for (std::size_t i = 1; i < 1001; ++i) {
                if (count[i] == num_sets) {
                    result.push_back(i);
                }
            }
            return result;
        }
    };

    TEST_CASE("2248 - Intersection of Multiple Arrays",
              "[Array][Hash Table][Sorting][Counting]") {

        SECTION("Example 1") {
            // Input: nums = [[3,1,2,4,5],[1,2,3,4],[3,4,5,6]]
            // Output: [3,4]
            Solution s;
            REQUIRE(
                s.intersection({{3, 1, 2, 4, 5}, {1, 2, 3, 4}, {3, 4, 5, 6}}) ==
                std::vector<int>{3, 4});
        }

        SECTION("Example 2") {
            // Input: nums = [[1,2,3],[4,5,6]]
            // Output: []
            Solution s;
            REQUIRE(s.intersection({{1, 2, 3}, {4, 5, 6}}) ==
                    std::vector<int>{});
        }
    }
} // namespace P2248
