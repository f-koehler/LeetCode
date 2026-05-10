#include <array>
#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace LeetCode::P0036 {
    class Solution {
      public:
        [[nodiscard]] static constexpr bool is_blank(const char entry) noexcept
            pre((entry == '.') || ((entry >= '1') && (entry <= '9'))) {
            return entry == '.';
        }
        [[nodiscard]] static constexpr std::size_t
        digit_index(const char digit) noexcept
            pre((digit >= '1') && (digit <= '9')) post(index : index < 9) {
            return digit - '1';
        }

        [[nodiscard]]
        static constexpr bool
        isValidSudoku(const std::vector<std::vector<char>> &board) noexcept
            pre(board.size() == 9) {

            // std::array to encode a hash set -> no memory allocations ->
            // constexpr & noexcept specifiers
            std::array<bool, 9> encountered_digits;

            // we check all conditions separately:
            // - otherwise we would need more stack memory: one 9-element buffer
            // per row, column, and cell
            // - the loops are tiny anyways with compile-time known bounds ->
            // loops will be unrolled and instructions should be reordered for
            // best memory access

            // check rows
            for (std::size_t row = 0; row < 9; ++row) {
                contract_assert(board[row].size() == 9);
                encountered_digits.fill(false);
                for (std::size_t col = 0; col < 9; ++col) {
                    const char entry = board[row][col];
                    contract_assert((entry == '.') ||
                                    ((entry >= '1') && (entry <= '9')));
                    if (is_blank(entry)) {
                        continue;
                    }
                    const std::size_t index = digit_index(entry);
                    if (encountered_digits[index]) {
                        return false;
                    }
                    encountered_digits[index] = true;
                }
            }

            // check cols
            for (std::size_t col = 0; col < 9; ++col) {
                encountered_digits.fill(false);
                for (std::size_t row = 0; row < 9; ++row) {
                    const char entry = board[row][col];
                    if (is_blank(entry)) {
                        continue;
                    }
                    const std::size_t index = digit_index(entry);
                    if (encountered_digits[index]) {
                        return false;
                    }
                    encountered_digits[index] = true;
                }
            }

            // check per cell
            for (std::size_t base_row = 0; base_row < 9; base_row += 3) {
                for (std::size_t base_col = 0; base_col < 9; base_col += 3) {
                    encountered_digits.fill(false);
                    for (std::size_t local_row = 0; local_row < 3;
                         ++local_row) {
                        for (std::size_t local_col = 0; local_col < 3;
                             ++local_col) {
                            const char entry = board[base_row + local_row]
                                                    [base_col + local_col];
                            if (is_blank(entry)) {
                                continue;
                            }
                            const std::size_t index = digit_index(entry);
                            if (encountered_digits[index]) {
                                return false;
                            }
                            encountered_digits[index] = true;
                        }
                    }
                }
            }

            return true;
        }
    };

    TEST_CASE("0036 - Valid Sudoku", "[Array][Hash Table][Matrix]") {
        SECTION("is_blank") {
            REQUIRE(Solution::is_blank('.'));
            REQUIRE(!Solution::is_blank('1'));
            REQUIRE(!Solution::is_blank('2'));
            REQUIRE(!Solution::is_blank('3'));
            REQUIRE(!Solution::is_blank('4'));
            REQUIRE(!Solution::is_blank('5'));
            REQUIRE(!Solution::is_blank('6'));
            REQUIRE(!Solution::is_blank('7'));
            REQUIRE(!Solution::is_blank('8'));
            REQUIRE(!Solution::is_blank('9'));
        }

        SECTION("digit_index") {
            REQUIRE(Solution::digit_index('1') == 0);
            REQUIRE(Solution::digit_index('2') == 1);
            REQUIRE(Solution::digit_index('3') == 2);
            REQUIRE(Solution::digit_index('4') == 3);
            REQUIRE(Solution::digit_index('5') == 4);
            REQUIRE(Solution::digit_index('6') == 5);
            REQUIRE(Solution::digit_index('7') == 6);
            REQUIRE(Solution::digit_index('8') == 7);
            REQUIRE(Solution::digit_index('9') == 8);
        }

        SECTION("Example 1") {
            const std::vector<std::vector<char>> board = {
                {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
            // Output: true
            REQUIRE(Solution::isValidSudoku(board));
        }

        SECTION("Example 2") {
            const std::vector<std::vector<char>> board = {
                {'8', '3', '.', '.', '7', '.', '.', '.', '.'},
                {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
            // Output: false
            REQUIRE(!Solution::isValidSudoku(board));
        }
    }
} // namespace LeetCode::P0036
