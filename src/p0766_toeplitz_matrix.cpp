#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P0766 {
    class Solution {
      public:
        bool isToeplitzMatrix(const std::vector<std::vector<int>> &matrix) {
            const std::size_t rows = matrix.size();
            const std::size_t cols = matrix.front().size();
            for (std::size_t row = 0; row + 1 < rows; ++row) {
                for (std::size_t col = 0; col + 1 < cols; ++col) {
                    if (matrix[row][col] != matrix[row + 1][col + 1]) {
                        return false;
                    }
                }
            }
            return true;
        }
    };

    TEST_CASE("0766 - Toeplitz Matrix", "[Array][Matrix]") {

        SECTION("Example 1") {
            // Input: matrix = [[1,2,3,4],[5,1,2,3],[9,5,1,2]]
            // Output: true
            Solution s;
            REQUIRE(
                s.isToeplitzMatrix({{1, 2, 3, 4}, {5, 1, 2, 3}, {9, 5, 1, 2}}));
        }

        SECTION("Example 2") {
            // Input: matrix = [[1,2],[2,2]]
            // Output: false
            Solution s;
            REQUIRE(!s.isToeplitzMatrix({{1, 2}, {2, 2}}));
        }
    }
} // namespace P0766
