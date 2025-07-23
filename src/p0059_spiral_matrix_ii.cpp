#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P0059 {
    class Solution {
      public:
        std::vector<std::vector<int>> generateMatrix(int n) {
            std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));

            int num_loops = n / 2;
            int next_element = 1;

            for (int loop = 0; loop < num_loops; ++loop) {
                int length =
                    n - loop - 1; // -1 to prevent overlap of the four loops
                for (int col = loop; col < length; ++col) {
                    result[loop][col] = next_element++;
                }
                for (int row = loop; row < length; ++row) {
                    result[row][length] = next_element++;
                }
                for (int col = length; col > loop; --col) {
                    result[length][col] = next_element++;
                }
                for (int row = length; row > loop; --row) {
                    result[row][loop] = next_element++;
                }
            }

            // handle case of n being odd -> center element
            if (n % 2) {
                result[n / 2][n / 2] = next_element;
            }

            return result;
        }
    };

    TEST_CASE("0059 - Spiral Matrix II", "[Array][Matrix][Simulation]") {

        SECTION("Example 1") {
            // Input: n = 3
            // Output: [[1,2,3],[8,9,4],[7,6,5]]
            Solution s;
            const int n = 3;
            const std::vector<std::vector<int>> output = s.generateMatrix(n);
            const std::vector<std::vector<int>> expected{
                {1, 2, 3}, {8, 9, 4}, {7, 6, 5}};
            REQUIRE(output.size() == n);
            for (std::size_t i = 0; i < expected.size(); ++i) {
                REQUIRE(output[i].size() == n);
                for (std::size_t j = 0; j < expected.size(); ++j) {
                    INFO(i << ',' << j);
                    REQUIRE(output[i][j] == expected[i][j]);
                }
            }
        }

        SECTION("Example 2") {
            // Input: n = 1
            // Output: [[1]]
            Solution s;
            const int n = 1;
            const std::vector<std::vector<int>> output = s.generateMatrix(n);
            const std::vector<std::vector<int>> expected{{1}};
            REQUIRE(output.size() == n);
            for (std::size_t i = 0; i < expected.size(); ++i) {
                REQUIRE(output[i].size() == n);
                for (std::size_t j = 0; j < expected.size(); ++j) {
                    INFO(i << ',' << j);
                    REQUIRE(output[i][j] == expected[i][j]);
                }
            }
        }
    }
} // namespace P0059
