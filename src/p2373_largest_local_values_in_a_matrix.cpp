#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P2373 {
    class Solution {
      public:
        std::vector<std::vector<int>>
        largestLocal(const std::vector<std::vector<int>> &grid) {
            const std::size_t n = grid.size();

            // result array of correct size
            //
            // initialize with 0, which will be smaller than all numbers in the
            // grid (range 1 to 100)
            std::vector<std::vector<int>> result(n - 2,
                                                 std::vector<int>(n - 2, 0));

            // row major storage order ->
            for (std::size_t row = 0; row < n - 2; ++row) {
                for (std::size_t col = 0; col < n - 2; ++col) {
                    for (std::size_t i = 0; i < 3; ++i) {
                        for (std::size_t j = 0; j < 3; ++j) {
                            result[row][col] = std::max(result[row][col],
                                                        grid[row + i][col + j]);
                        }
                    }
                }
            }

            return result;
        }
    };

    TEST_CASE("2373 - Largest Local Values in a Matrix", "[Array][Matrix]") {

        SECTION("Example 1") {
            // Input: grid = [[9,9,8,1],[5,6,2,6],[8,2,6,4],[6,2,2,2]]
            // Output: [[9,9],[8,6]]
            Solution s;
            const std::vector<std::vector<int>> result = s.largestLocal(
                {{9, 9, 8, 1}, {5, 6, 2, 6}, {8, 2, 6, 4}, {6, 2, 2, 2}});
            REQUIRE(result.size() == 2);
            REQUIRE(result.front().size() == 2);
            REQUIRE(result == std::vector<std::vector<int>>{{9, 9}, {8, 6}});
        }

        SECTION("Example 2") {
            // Input: grid =
            // [[1,1,1,1,1],[1,1,1,1,1],[1,1,2,1,1],[1,1,1,1,1],[1,1,1,1,1]]
            // Output: [[2,2,2],[2,2,2],[2,2,2]]
            Solution s;
            const std::vector<std::vector<int>> result =
                s.largestLocal({{1, 1, 1, 1, 1},
                                {1, 1, 1, 1, 1},
                                {1, 1, 2, 1, 1},
                                {1, 1, 1, 1, 1},
                                {1, 1, 1, 1, 1}});
            REQUIRE(result.size() == 3);
            REQUIRE(result.front().size() == 3);
            REQUIRE(result == std::vector<std::vector<int>>{
                                  {2, 2, 2}, {2, 2, 2}, {2, 2, 2}});
        }
    }
} // namespace P2373
