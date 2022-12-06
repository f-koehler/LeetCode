#include <catch2/catch_test_macros.hpp>
#include <vector>
using namespace std;

class Solution {
  public:
    void floodFillDFS(vector<vector<int>> &image, const int r, const int c,
                      const int color, const int old_color) {
        if ((r < 0) || (r >= static_cast<int>(image.size())) || (c < 0) ||
            (c >= static_cast<int>(image[0].size()))) {
            return;
        }

        const auto current_color = image[r][c];

        if ((current_color != old_color) || (current_color == color))
            return;

        image[r][c] = color;
        floodFillDFS(image, r - 1, c, color, old_color);
        floodFillDFS(image, r + 1, c, color, old_color);
        floodFillDFS(image, r, c - 1, color, old_color);
        floodFillDFS(image, r, c + 1, color, old_color);
    }

    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc,
                                  int color) {
        const int old_color = image[sr][sc];
        floodFillDFS(image, sr, sc, color, old_color);
        return image;
    }
};

TEST_CASE("0733 - Flood Fill",
          "[Array][Depth-First Search][Breadth-First Search][Matrix]") {
    Solution s;
    SECTION("Example 1") {
        vector<vector<int>> image = {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}};
        vector<vector<int>> expected = {{2, 2, 2}, {2, 2, 0}, {2, 0, 1}};
        REQUIRE(s.floodFill(image, 1, 1, 2) == expected);
    }
    SECTION("Example 2") {
        vector<vector<int>> image = {{0, 0, 0}, {0, 0, 0}};
        vector<vector<int>> expected = {{0, 0, 0}, {0, 0, 0}};
        REQUIRE(s.floodFill(image, 0, 0, 0) == expected);
    }
}