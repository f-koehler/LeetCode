#include <catch2/catch_test_macros.hpp>
#include <vector>
using namespace std;

class Solution {
  public:
    vector<vector<int>> matrixReshape(vector<vector<int>> &mat, int r, int c) {
        int m = mat.size();
        int n = mat[0].size();

        if (m * n != r * c) {
            return mat;
        }

        vector<vector<int>> result(r, vector<int>(c));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int index = i * n + j;
                result[index / c][index % c] = mat[i][j];
            }
        }
        return result;
    }
};

TEST_CASE("0566 - Reshape the Matrix", "[Array][Matrix][Simulation]") {
    Solution s;
    SECTION("Example 1") {
        vector<vector<int>> mat = {{1, 2}, {3, 4}};
        auto result = s.matrixReshape(mat, 1, 4);
        REQUIRE(result == vector<vector<int>>({{1, 2, 3, 4}}));
    }
    SECTION("Example 2") {
        vector<vector<int>> mat = {{1, 2}, {3, 4}};
        auto result = s.matrixReshape(mat, 2, 4);
        REQUIRE(result == vector<vector<int>>({{1, 2}, {3, 4}}));
    }
}