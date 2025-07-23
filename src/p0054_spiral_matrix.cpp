#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P0054 {
    class Solution {
      public:
        std::vector<int>
        spiralOrder(const std::vector<std::vector<int>> &matrix) {
            std::vector<int> result;
            const std::size_t num_rows = matrix.size();
            const std::size_t num_cols = matrix[0].size();
            const std::size_t num_elements = num_rows * num_cols;
            result.reserve(num_elements);

            int row_min = 0;
            int row_max = num_rows - 1;
            int col_min = 0;
            int col_max = num_cols - 1;

            while (result.size() < num_elements) {
                for (int col = col_min;
                     (col <= col_max) && (result.size() < num_elements);
                     ++col) {
                    result.push_back(matrix[row_min][col]);
                }
                for (int row = row_min + 1;
                     (row <= row_max - 1) && (result.size() < num_elements);
                     ++row) {
                    result.push_back(matrix[row][col_max]);
                }
                for (int col = col_max;
                     (col >= col_min) && (result.size() < num_elements);
                     --col) {
                    result.push_back(matrix[row_max][col]);
                }
                for (int row = row_max - 1;
                     (row >= row_min + 1) && (result.size() < num_elements);
                     --row) {
                    result.push_back(matrix[row][col_min]);
                }
                ++row_min;
                --row_max;
                ++col_min;
                --col_max;
            }
            return result;
        }
    };

    TEST_CASE("0054 - Spiral Matrix", "[Array][Matrix][Simulation]") {

        SECTION("Example 1") {
            // Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
            // Output: [1,2,3,6,9,8,7,4,5]
            Solution s;

            const std::vector<std::vector<int>> input{
                {1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
            const std::vector<int> expected{1, 2, 3, 6, 9, 8, 7, 4, 5};
            const std::vector<int> output = s.spiralOrder(input);
            REQUIRE(output.size() == expected.size());
            for (std::size_t i = 0; i < expected.size(); ++i) {
                INFO(i);
                REQUIRE(output[i] == expected[i]);
            }
        }

        SECTION("Example 2") {
            // Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
            // Output: [1,2,3,4,8,12,11,10,9,5,6,7]
            Solution s;
            const std::vector<std::vector<int>> input{
                {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
            const std::vector<int> expected{1,  2,  3, 4, 8, 12,
                                            11, 10, 9, 5, 6, 7};
            const std::vector<int> output = s.spiralOrder(input);
            REQUIRE(output.size() == expected.size());
            for (std::size_t i = 0; i < expected.size(); ++i) {
                INFO(i);
                REQUIRE(output[i] == expected[i]);
            }
        }
    }
} // namespace P0054
