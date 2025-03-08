#include <catch2/catch_test_macros.hpp>
#include <vector>
using namespace std;

namespace P0118 {
    class Solution {
      public:
        vector<vector<int>> generate(int numRows) {
            if (numRows == 1) {
                return {{1}};
            }

            vector<vector<int>> result{{1}, {1, 1}};
            for (int row = 2; row < numRows; ++row) {
                vector<int> new_row(row + 1, 1);
                for (int col = 1; col < row; ++col) {
                    new_row[col] =
                        result[row - 1][col - 1] + result[row - 1][col];
                }
                result.push_back(new_row);
            }
            return result;
        }
    };

    TEST_CASE("0118 - Pascal's Triangle", "[Array][Dynamic Programming]") {
        Solution s;
        SECTION("Example 1") {
            auto result = s.generate(5);
            REQUIRE(
                result ==
                vector<vector<int>>(
                    {{1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}, {1, 4, 6, 4, 1}}));
        }
        SECTION("Example 2") {
            auto result = s.generate(1);
            REQUIRE(result == vector<vector<int>>({{1}}));
        }
    }
} // namespace P0118