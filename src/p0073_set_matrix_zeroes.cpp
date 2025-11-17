#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P0073 {
    class Solution {
      public:
        void setZeroes(std::vector<std::vector<int>> &matrix) {
            // first index -> row
            // second index -> column

            const std::size_t rows = matrix.size();
            const std::size_t cols = matrix.front().size();

            // use first cell of each row/column as a flag that the
            // corresponding row/column should be set to zero

            // first we need to check if the first row/column need to be filled
            // otherwise we would encounter a problem when doing the actual
            // filling
            const bool fill_first_row =
                std::find(matrix.front().cbegin(), matrix.front().cend(), 0) !=
                matrix.front().cend();
            bool fill_first_col = false;
            for (std::size_t row = 0; row < rows; ++row) {
                if (matrix[row][0] == 0) {
                    fill_first_col = true;
                    break;
                }
            }

            // check which other rows and columns need to be filled
            for (std::size_t row = 1; row < rows; ++row) {
                for (std::size_t col = 1; col < cols; ++col) {
                    if (matrix[row][col] == 0) {
                        matrix[0][col] = 0;
                        matrix[row][0] = 0;
                    }
                }
            }

            // fill all elements except first row and column
            for (std::size_t row = 1; row < rows; ++row) {
                for (std::size_t col = 1; col < cols; ++col) {
                    if (matrix[0][col] == 0 || matrix[row][0] == 0) {
                        matrix[row][col] = 0;
                    }
                }
            }

            if (fill_first_row) {
                std::fill(matrix.front().begin(), matrix.front().end(), 0);
            }
            if (fill_first_col) {
                for (std::size_t row = 0; row < rows; ++row) {
                    matrix[row][0] = 0;
                }
            }
        }
    };

    TEST_CASE("0073 - Set Matrix Zeroes", "[Array][Hash Table][Matrix]") {

        SECTION("Example 1") {
            // Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
            // Output: [[1,0,1],[0,0,0],[1,0,1]]
            Solution s;
            std::vector<std::vector<int>> matrix = {
                {1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
            s.setZeroes(matrix);
            std::vector<std::vector<int>> expected = {
                {1, 0, 1}, {0, 0, 0}, {1, 0, 1}};
            REQUIRE(matrix == expected);
        }

        SECTION("Example 2") {
            // Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
            // Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
            Solution s;
            std::vector<std::vector<int>> matrix = {
                {0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}};
            s.setZeroes(matrix);
            std::vector<std::vector<int>> expected = {
                {0, 0, 0, 0}, {0, 4, 5, 0}, {0, 3, 1, 0}};
            REQUIRE(matrix == expected);
        }

        SECTION("Example 3") {
            // Input: matrix = [[1],[0]]
            // Output: matrix = [[0],[0]]
            Solution s;
            std::vector<std::vector<int>> matrix = {{1}, {0}};
            s.setZeroes(matrix);
            std::vector<std::vector<int>> expected = {{0}, {0}};
            REQUIRE(matrix == expected);
        }
    }
} // namespace P0073
