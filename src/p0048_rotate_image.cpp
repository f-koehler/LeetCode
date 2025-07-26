#include <array>
#include <catch2/catch_test_macros.hpp>
#include <utility>
#include <vector>

namespace P0048 {
    class Solution {
      public:
        void rotate(std::vector<std::vector<int>> &matrix) {
            const std::size_t n = matrix.size();

            // step 1: transpose matrix
            for (std::size_t i = 0; i < n; ++i) {
                for (std::size_t j = 0; j < i; ++j) {
                    std::swap(matrix[i][j], matrix[j][i]);
                }
            }

            // step 2: flip matrix along vertical axis
            const std::size_t n_half = n / 2;
            for (std::size_t i = 0; i < n; ++i) {
                for (std::size_t j = 0; j < n_half; ++j) {
                    std::swap(matrix[i][j], matrix[i][n - j - 1]);
                }
            }
        }
    };

    TEST_CASE("0048 - Rotate Image", "[Array][Math][Matrix]") {

        SECTION("Example 1") {
            // Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
            // Output: [[7,4,1],[8,5,2],[9,6,3]]
            Solution s;

            std::vector<std::vector<int>> matrix{
                {1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
            s.rotate(matrix);
            REQUIRE(matrix == std::vector<std::vector<int>>{
                                  {7, 4, 1}, {8, 5, 2}, {9, 6, 3}});
        }

        SECTION("Example 2") {
            // Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
            // Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
            Solution s;

            std::vector<std::vector<int>> matrix{
                {5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}};
            s.rotate(matrix);
            REQUIRE(matrix == std::vector<std::vector<int>>{{15, 13, 2, 5},
                                                            {14, 3, 4, 1},
                                                            {12, 6, 8, 9},
                                                            {16, 7, 10, 11}});
        }
    }
} // namespace P0048
