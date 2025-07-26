#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P0867 {
    class Solution {
      public:
        std::vector<std::vector<int>>
        transpose(const std::vector<std::vector<int>> &matrix) {
            const std::size_t rows = matrix.size();
            const std::size_t cols =
                matrix.front().size(); // at least one row guaranteed

            std::vector<std::vector<int>> result(cols,
                                                 std::vector<int>(rows, 0));

            for (std::size_t col = 0; col < cols; ++col) {
                for (std::size_t row = 0; row < rows; ++row) {
                    result[col][row] = matrix[row][col];
                }
            }

            return result;
        }
    };

    TEST_CASE("0867 - Transpose Matrix", "[Array][Matrix][Simulation]") {

        SECTION("Example 1") {
            // Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
            // Output: [[1,4,7],[2,5,8],[3,6,9]]
            Solution s;
            const std::vector<std::vector<int>> result =
                s.transpose({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
            const std::vector<std::vector<int>> expected{
                {1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
            REQUIRE(result.size() == 3);
            REQUIRE(result.front().size() == 3);
            for (std::size_t col = 0; col < 3; ++col) {
                for (std::size_t row = 0; row < 3; ++row) {
                    INFO("Element " << row << ',' << col);
                    REQUIRE(result[row][col] == expected[row][col]);
                }
            }
        }

        SECTION("Example 2") {
            // Input: matrix = [[1,2,3],[4,5,6]]
            // Output: [[1,4],[2,5],[3,6]]
            Solution s;
            const std::vector<std::vector<int>> result =
                s.transpose({{1, 2, 3}, {4, 5, 6}});
            const std::vector<std::vector<int>> expected{
                {1, 4}, {2, 5}, {3, 6}};
            REQUIRE(result.size() == 3);
            REQUIRE(result.front().size() == 2);
            for (std::size_t col = 0; col < 2; ++col) {
                for (std::size_t row = 0; row < 3; ++row) {
                    INFO("Element " << row << ',' << col);
                    REQUIRE(result[row][col] == expected[row][col]);
                }
            }
        }
    }
} // namespace P0867
