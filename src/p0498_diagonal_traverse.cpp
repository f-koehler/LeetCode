#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P0498 {
    class Solution {
      public:
        std::vector<int>
        findDiagonalOrder(const std::vector<std::vector<int>> &mat) {
            const int m = mat.size();
            const int n = mat.front().size();
            const int num_elements = m * n;

            std::vector<int> result(m * n);

            int row = 0;
            int col = 0;

            // 1: bottom-left to top-right
            // -1: top-right to bottom-left
            int direction = 1;

            // we start with the first element and simulate the walking pattern
            for (int index = 0; index < num_elements; ++index) {
                result[index] = mat[row][col];

                row -= direction;
                col += direction;

                // check if row hits bottom border
                if (row == m) {
                    direction = -direction;
                    row = m - 1; // reset to lowest row
                    col += 2;    // have to advance column twice
                }

                // check if col hits right border
                if (col == n) {
                    direction = -direction;
                    col = n - 1; // rest to right most column
                    row += 2;    // have to advance column twice
                }

                // check if row hits top border
                if (row < 0) {
                    row = 0;
                    direction = -direction;
                }

                // check if col hits left border
                if (col < 0) {
                    col = 0;
                    direction = -direction;
                }
            }

            return result;
        }
    };

    TEST_CASE("0498 - Diagonal Traverse", "[Array][Matrix][Simulation]") {

        SECTION("Example 1") {
            // Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
            // Output: [1,2,4,7,5,3,6,8,9]
            Solution s;
            REQUIRE(s.findDiagonalOrder({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}) ==
                    std::vector<int>{1, 2, 4, 7, 5, 3, 6, 8, 9});
        }

        SECTION("Example 2") {
            // Input: mat = [[1,2],[3,4]]
            // Output: [1,2,3,4]
            Solution s;
            REQUIRE(s.findDiagonalOrder({{1, 2}, {3, 4}}) ==
                    std::vector<int>{1, 2, 3, 4});
        }
    }
} // namespace P0498
