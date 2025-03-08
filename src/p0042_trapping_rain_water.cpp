#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P0042 {
    class Solution {
      public:
        int trap(const std::vector<int> &height) {
            const std::size_t n = height.size();

            // edge cases
            if (n < 3) {
                return 0;
            }

            std::vector<int> max_height_to_left(n, 0);
            std::vector<int> max_height_to_right(n, 0);

            max_height_to_left[0] = height[0];
            max_height_to_right[n - 1] = height[n - 1];

            // find the maximum height up to and including column i from the
            // left
            for (std::size_t i = 1; i < n; ++i) {
                max_height_to_left[i] =
                    std::max(max_height_to_left[i - 1], height[i]);
            }

            // find the maximum height up to and including column i from the
            // right
            for (int i = n - 2; i >= 0; --i) {
                max_height_to_right[i] =
                    std::max(max_height_to_right[i + 1], height[i]);
            }

            int trapped_water = 0;
            for (std::size_t i = 0; i < n; ++i) {
                // Compute the amount of water that can be trapped at column i.
                // Firstly, find the minimum of the maximum height to the left
                // and right, the water cannot be higher than that. Secondly,
                // subtract the height of the column itself.
                trapped_water +=
                    std::min(max_height_to_left[i], max_height_to_right[i]) -
                    height[i];
            }
            return trapped_water;
        }
    };

    TEST_CASE(
        "0042 - Trapping Rain Water",
        "[Array][Two Pointers][Dynamic Programming][Stack][Monotonic Stack]") {
        SECTION("Example 1") {
            Solution solution;
            REQUIRE(solution.trap({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}) == 6);
        }
        SECTION("Example 2") {
            Solution solution;
            REQUIRE(solution.trap({4, 2, 0, 3, 2, 5}) == 9);
        }
        SECTION("Example 3") {
            Solution solution;
            REQUIRE(solution.trap({2, 0, 2}) == 2);
        }
        SECTION("Example 4") {
            Solution solution;
            REQUIRE(solution.trap({0, 1, 0}) == 0);
        }
    }
} // namespace P0042