#include <array>
#include <catch2/catch_test_macros.hpp>
#include <concepts>
#include <cstddef>
#include <vector>
#include "./p0046_precompute.hpp"

namespace P0046 {

    // compile-time factorial function
    template <std::integral Integer>
    consteval Integer factorial(Integer n) {
        return n == 0 ? 1 : n * factorial(n - 1);
    }

    template <std::integral Integer>
    constexpr std::array<Integer, 7> factorials = {
        factorial(0), factorial(1), factorial(2), factorial(3),
        factorial(4), factorial(5), factorial(6)};

    class Solution {
      public:
        [[nodiscard]] std::vector<std::vector<int>>
        permute(std::vector<int> &nums) noexcept {
            const int n = nums.size();
            const int n_factorial = factorials<int>[n];
        }

        [[nodiscard]] std::vector<std::vector<int>>
        permute_lookup(const std::vector<int> &nums) noexcept {
            const std::size_t n = nums.size();
            const std::size_t n_factorial = factorials<std::size_t>[n];
            const auto [table, _] = p0046::get_permutations_for_size(n);

            std::vector<std::vector<int>> result(n_factorial, std::vector<int>(n));
            for(std::size_t i = 0; i < n_factorial; ++i) {
                for(std::size_t j = 0; j < n; ++j) {
                    result[i][j] = nums[table[i * n + j]];
                }
            }
            return result;
        }
    };

    TEST_CASE("0046 - Permutations", "[Array][Backtracking]") {

        SECTION("Example 1") {
            // Input: nums = [1,2,3]
            // Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
            Solution s;

            SECTION("Lookup") {
                const auto result = s.permute_lookup(std::vector<int>{1,2,3});
                REQUIRE(result.size() == 6);
                REQUIRE(result[0].size() == 3);
                REQUIRE(result[1].size() == 3);
                REQUIRE(result[2].size() == 3);
                REQUIRE(result[3].size() == 3);
                REQUIRE(result[4].size() == 3);
                REQUIRE(result[5].size() == 3);
                REQUIRE(result[0] == std::vector<int>{1,2,3});
                REQUIRE(result[1] == std::vector<int>{1,3,2});
                REQUIRE(result[2] == std::vector<int>{2,1,3});
                REQUIRE(result[3] == std::vector<int>{2,3,1});
                REQUIRE(result[4] == std::vector<int>{3,1,2});
                REQUIRE(result[5] == std::vector<int>{3,2,1});
            }
        }

        SECTION("Example 2") {
            // Input: nums = [0,1]
            // Output: [[0,1],[1,0]]
            Solution s;

            SECTION("Lookup") {
                const auto result = s.permute_lookup({{0,1}});
                REQUIRE(result.size() == 2);
                REQUIRE(result[0].size() == 2);
                REQUIRE(result[1].size() == 2);
                REQUIRE(result[0] == std::vector<int>{0,1});
                REQUIRE(result[1] == std::vector<int>{1,0});
            }
        }

        SECTION("Example 3") {
            // Input: nums = [1]
            // Output: [[1]]
            Solution s;
            const auto result = s.permute_lookup(std::vector<int>{1});
            REQUIRE(result.size() == 1);
            REQUIRE(result[0].size() == 1);
            REQUIRE(result[0][0] == 1);
        }
    }
} // namespace P0046
