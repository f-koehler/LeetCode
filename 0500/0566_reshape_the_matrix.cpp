#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P0566 {
    class Solution {
      public:
        std::vector<std::vector<int>>
        matrixReshape(const std::vector<std::vector<int>> &mat, int r, int c) {
            int m = mat.size();
            int n = mat[0].size();

            if (m * n != r * c) {
                return mat;
            }

            std::vector<std::vector<int>> result(r, std::vector<int>(c));
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
            std::vector<std::vector<int>> mat = {{1, 2}, {3, 4}};
            auto result = s.matrixReshape(mat, 1, 4);
            REQUIRE(result == std::vector<std::vector<int>>({{1, 2, 3, 4}}));
        }
        SECTION("Example 2") {
            std::vector<std::vector<int>> mat = {{1, 2}, {3, 4}};
            auto result = s.matrixReshape(mat, 2, 4);
            REQUIRE(result == std::vector<std::vector<int>>({{1, 2}, {3, 4}}));
        }
    }
} // namespace P0566