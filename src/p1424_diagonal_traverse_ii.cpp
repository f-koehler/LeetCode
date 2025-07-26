#include <catch2/catch_test_macros.hpp>
#include <numeric>
#include <queue>
#include <vector>

namespace P1424 {

    struct Position {
        std::size_t row;
        std::size_t col;
    };

    class Solution {
      public:
        std::vector<int>
        findDiagonalOrder(const std::vector<std::vector<int>> &nums) {
            // if we imagine the array rotated by 45 degree, this is level order
            // traversal of a binary tree
            //
            // the left child is: same column but row+1
            // the right child is: same row but column+1
            //
            // we only need to check for a left child in column 0 to access each
            // element once

            // allocated result array
            const std::size_t num_elements = std::accumulate(
                nums.cbegin(), nums.cend(), std::size_t{0},
                [](const std::size_t &acc, const std::vector<int> &vec) {
                    return acc + vec.size();
                });
            std::vector<int> result;
            result.reserve(num_elements);

            // build a queue with nodes to visit
            const std::size_t rows = nums.size();
            std::queue<Position> to_process;
            to_process.emplace(0, 0);

            while (!to_process.empty()) {
                const Position next = to_process.front();
                to_process.pop();

                // add current element to result
                result.push_back(nums[next.row][next.col]);

                // add left child if possible if on first column
                if ((next.row + 1 < rows) && (next.col == 0)) {
                    // we can do this since rows cannot be empty
                    to_process.emplace(next.row + 1, next.col);
                }

                // add right child if possible
                if (next.col + 1 < nums[next.row].size()) {
                    to_process.emplace(next.row, next.col + 1);
                }
            }

            return result;
        }
    };

    TEST_CASE("1424 - Diagonal Traverse II",
              "[Array][Sorting][Heap (Priority Queue)]") {

        SECTION("Example 1") {
            // Input: nums = [[1,2,3],[4,5,6],[7,8,9]]
            // Output: [1,4,2,7,5,3,8,6,9]
            Solution s;
            const std::vector<int> result =
                s.findDiagonalOrder({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
            REQUIRE(result.size() == 9);
            REQUIRE(result == std::vector<int>{1, 4, 2, 7, 5, 3, 8, 6, 9});
        }

        SECTION("Example 2") {
            // Input: nums = [[1,2,3,4,5],[6,7],[8],[9,10,11],[12,13,14,15,16]]
            // Output: [1,6,2,8,7,3,9,4,12,10,5,13,11,14,15,16]
            Solution s;
            const std::vector<int> result =
                s.findDiagonalOrder({{1, 2, 3, 4, 5},
                                     {6, 7},
                                     {8},
                                     {9, 10, 11},
                                     {12, 13, 14, 15, 16}});
            REQUIRE(result.size() == 16);
            REQUIRE(result == std::vector<int>{1, 6, 2, 8, 7, 3, 9, 4, 12, 10,
                                               5, 13, 11, 14, 15, 16});
        }
    }
} // namespace P1424
