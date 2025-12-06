#include <catch2/catch_test_macros.hpp>
#include <queue>
#include <array>

namespace P0200 {
    class Solution {
    public:
        int numIslands(std::vector<std::vector<char>> &grid) {
            static constexpr std::array<std::pair<int, int>, 4> steps = {
                {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}
            };
            const int num_rows = static_cast<int>(grid.size());
            const int num_cols = static_cast<int>(grid.front().size());

            const auto visit_island_bfs = [&grid, &num_rows, &num_cols
                ](int start_row, int start_col) {
                std::queue<std::pair<int, int>> to_visit{
                    {{start_row, start_col}}};
                grid[start_row][start_col] = '2';
                while (!to_visit.empty()) {
                    const auto [row,col] = to_visit.front();
                    to_visit.pop();
                    for (const auto &[d_row, d_col] : steps) {
                        const int new_row = row + d_row;
                        const int new_col = col + d_col;
                        if ((new_row < 0) || (new_row >= num_rows) || (
                                new_col < 0) || (new_col >= num_cols)) {
                            continue;
                        }
                        if (grid[new_row][new_col] != '1') {
                            continue;
                        }
                        to_visit.emplace(new_row, new_col);
                        grid[new_row][new_col] = '2';
                    }
                }
            };

            int num_islands = 0;
            for (int row = 0; row < num_rows; ++row) {
                for (int col = 0; col < num_cols; ++col) {
                    if (grid[row][col] == '1') {
                        visit_island_bfs(row, col);
                        ++num_islands;
                    }
                }
            }

            return num_islands;
        }
    };

    TEST_CASE("0200 - Number of Islands",
              "[Array][Depth-First Search][Breadth-First Search][Union Find][Matrix]") {

        SECTION("Example 1") {
            // Input: grid = [
            //  ["1","1","1","1","0"],
            //  ["1","1","0","1","0"],
            //  ["1","1","0","0","0"],
            //  ["0","0","0","0","0"]
            //]
            // Output: 1
            Solution s;
            std::vector<std::vector<char>> grid = {
                {'1', '1', '1', '1', '0'},
                {'1', '1', '0', '1', '0'},
                {'1', '1', '0', '0', '0'},
                {'0', '0', '0', '0', '0'},
            };
            REQUIRE(s.numIslands(grid) == 1);
        }

        SECTION("Example 2") {
            // Input: grid = [
            //  ["1","1","0","0","0"],
            //  ["1","1","0","0","0"],
            //  ["0","0","1","0","0"],
            //  ["0","0","0","1","1"]
            //]
            // Output: 3
            Solution s;
            std::vector<std::vector<char>> grid = {
                {'1', '1', '0', '0', '0'},
                {'1', '1', '0', '0', '0'},
                {'0', '0', '1', '0', '0'},
                {'0', '0', '0', '1', '1'}
            };
            REQUIRE(s.numIslands(grid) == 3);
        }

    }
} // namespace P0200