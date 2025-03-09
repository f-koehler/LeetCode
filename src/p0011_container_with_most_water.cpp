#include <algorithm>
#include <cassert>
#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P0011 {
    class Solution {
      public:
        int maxArea(const std::vector<int> &height) {
            assert(height.size() >= 2);
            assert(std::all_of(height.begin(), height.end(),
                               [](int x) { return x >= 0; }));
            std::size_t left = 0;
            std::size_t right = height.size() - 1;
            int water = 0;
            while (left < right) {
                int new_water =
                    (right - left) * std::min(height[left], height[right]);
                water = std::max(water, new_water);
                if (height[right] > height[left]) {
                    ++left;
                } else {
                    --right;
                }
            }
            return water;
        }
    };

    TEST_CASE("0011 - Container With Most Water",
              "[Array][Two Pointers][Greedy]") {

        SECTION("Example 1") {
            // Input: height = [1,8,6,2,5,4,8,3,7]
            // Output: 49
            Solution s;
            REQUIRE(s.maxArea({1, 8, 6, 2, 5, 4, 8, 3, 7}) == 49);
        }

        SECTION("Example 2") {
            // Input: height = [1,1]
            // Output: 1
            Solution s;
            REQUIRE(s.maxArea({1, 1}) == 1);
        }

        SECTION("Example 3") {
            // Input: height = [8,7,2,1]
            // Output: 7
            Solution s;
            REQUIRE(s.maxArea({8, 7, 2, 1}) == 7);
        }
    }
} // namespace P0011