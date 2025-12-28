#include <catch2/catch_test_macros.hpp>
#include <queue>
#include <utility>
#include <vector>

namespace P0973 {
    class Solution {
      public:
        [[nodiscard]] std::vector<std::vector<int>>
        kClosest(const std::vector<std::vector<int>> &points, int k) {
            // max heap storing a pair of (distance to origin, point)
            std::priority_queue<std::pair<int, std::pair<int, int>>> k_closest;
            for (const auto &point : points) {
                int x = point[0];
                int y = point[1];
                k_closest.push({x * x + y * y, {x, y}});
                if (k_closest.size() > k) {
                    k_closest.pop();
                }
            }
            std::vector<std::vector<int>> result;
            result.reserve(k);
            while (!k_closest.empty()) {
                result.emplace_back(
                    std::vector<int>{k_closest.top().second.first,
                                     k_closest.top().second.second});
                k_closest.pop();
            }
            return result;
        }
    };

    TEST_CASE("0973 - K Closest Points to Origin",
              "[Array][Math][Divide and Conquer][Geometry][Sorting][Heap "
              "(Priority Queue)][Quickselect]") {

        SECTION("Example 1") {
            // Input: points = [[1,3],[-2,2]], k = 1
            // Output: [[-2,2]]
            Solution s;
            const auto result = s.kClosest({{1, 3}, {-2, 2}}, 1);
            REQUIRE(result.size() == 1);
            REQUIRE(result.front().front() == -2);
            REQUIRE(result.front().back() == 2);
        }

        SECTION("Example 2") {
            // Input: points = [[3,3],[5,-1],[-2,4]], k = 2
            // Output: [[3,3],[-2,4]]
            Solution s;
            const auto result = s.kClosest({{3, 3}, {5, -1}, {-2, 4}}, 2);
            REQUIRE(result.size() == 2);
            REQUIRE(result.front().front() == -2);
            REQUIRE(result.front().back() == 4);
            REQUIRE(result.back().front() == 3);
            REQUIRE(result.back().back() == 3);
        }
    }
} // namespace P0973