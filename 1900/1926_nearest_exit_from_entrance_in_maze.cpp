#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <queue>
#include <tuple>
#include <vector>

struct Position {
    int row;
    int col;
    int dist;
};

class Solution {
  public:
    int nearestExit(const std::vector<std::vector<char>> &maze,
                    const std::vector<int> &entrance) {
        const int num_rows = maze.size();
        const int num_cols = maze.front().size();
        std::vector<std::vector<bool>> visited;
        visited.reserve(num_rows);
        std::generate_n(std::back_inserter(visited), num_rows, [&num_cols]() {
            return std::vector<bool>(num_cols, false);
        });

        std::queue<Position> next_fields;
        next_fields.push({entrance.at(0), entrance.at(1), 0});

        while (!next_fields.empty()) {
            Position pos = next_fields.front();
            next_fields.pop();

            // check if we already visited the position
            if (visited[pos.row][pos.col]) {
                continue;
            }

            // mark as visited
            visited[pos.row][pos.col] = true;

            // check if position is a wall
            if (maze[pos.row][pos.col] == '+') {
                continue;
            }

            // check if exit, i.e. position is on the border and we have
            // travelled at least one step
            if (((pos.row == 0) || (pos.col == 0) ||
                 (pos.row + 1 == num_rows) || (pos.col + 1 == num_cols)) &&
                (pos.dist > 0)) {
                return pos.dist;
            }

            if (int new_row = pos.row - 1; new_row >= 0) {
                // explore field above
                next_fields.push({new_row, pos.col, pos.dist + 1});
            }
            if (int new_row = pos.row + 1; new_row < num_rows) {
                // explore field below
                next_fields.push({new_row, pos.col, pos.dist + 1});
            }
            if (int new_col = pos.col - 1; new_col >= 0) {
                // explore field to the left
                next_fields.push({pos.row, new_col, pos.dist + 1});
            }
            if (int new_col = pos.col + 1; new_col < num_cols) {
                // explore field to the right
                next_fields.push({pos.row, new_col, pos.dist + 1});
            }
        }

        return -1;
    }
};

TEST_CASE("1926 - Nearest Exit from Entrance in Maze",
          "[Array][Breadth-First Search][Matrix]") {
    Solution s;
    SECTION("Example 1") {
        REQUIRE(s.nearestExit({{'+', '+', '.', '+'},
                               {'.', '.', '.', '+'},
                               {'+', '+', '+', '.'}},
                              {1, 2}) == 1);
    }
    SECTION("Example 2") {
        REQUIRE(
            s.nearestExit({{'+', '+', '+'}, {'.', '.', '.'}, {'+', '+', '+'}},
                          {1, 0}) == 2);
    }
    SECTION("Example 3") { REQUIRE(s.nearestExit({{'.', '+'}}, {0, 0}) == -1); }
}
