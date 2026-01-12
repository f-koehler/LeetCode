#include <catch2/catch_test_macros.hpp>
#include <ranges>
#include <stack>
#include <vector>

namespace P0739 {
    class Solution {
      public:
        [[nodiscard]]
        std::vector<int>
        dailyTemperatures(const std::vector<int> &temperatures) {
            std::vector<int> result(temperatures.size(), 0);

            // stack of index/temperature still waiting for a warmer temperature
            std::stack<std::size_t> stack;
            for (const auto [index, temperature] :
                 std::views::enumerate(temperatures)) {
                while (!stack.empty() &&
                       (temperature > temperatures[stack.top()])) {
                    result[stack.top()] = static_cast<int>(index - stack.top());
                    stack.pop();
                }
                stack.emplace(index);
            }
            return result;
        }

        [[nodiscard]]
        std::vector<int>
        dailyTemperaturesDP(const std::vector<int> &temperatures) {
            const int n = temperatures.size();
            std::vector<int> result(n, 0);

            // traverse the array in reverse order
            for (int i = n - 2; i >= 0; --i) {
                // for each temperature t_i check temperatures t_j to the right
                const int t = temperatures[i];
                int j = i + 1;

                // loop j while t_j is not larger and j is in bounds
                while ((j < n) && (temperatures[j] <= t)) {
                    // if we hit a zero, we know that there is no warmer
                    // temperature to the right (t_k <= t_j), we can break
                    if (result[j] == 0) {
                        j = n;
                        break;
                    }

                    // otherwise we can skip ahead to the temperature that is
                    // warmer than t_j
                    j += result[j];
                }

                // if we stayed in bounds, we found a warmer temperature
                if (j < n) {
                    result[i] = j - i;
                }
            }

            return result;
        }
    };

    TEST_CASE("0739 - Daily Temperatures",
              "[Array][Stack][Monotonic Stack][NeetCode150]") {

        SECTION("Example 1") {
            // Input: temperatures = [73,74,75,71,69,72,76,73]
            // Output: [1,1,4,2,1,1,0,0]
            Solution s;
            REQUIRE(s.dailyTemperatures({73, 74, 75, 71, 69, 72, 76, 73}) ==
                    std::vector<int>{1, 1, 4, 2, 1, 1, 0, 0});
            REQUIRE(s.dailyTemperaturesDP({73, 74, 75, 71, 69, 72, 76, 73}) ==
                    std::vector<int>{1, 1, 4, 2, 1, 1, 0, 0});
        }

        SECTION("Example 2") {
            // Input: temperatures = [30,40,50,60]
            // Output: [1,1,1,0]
            Solution s;
            REQUIRE(s.dailyTemperatures({30, 40, 50, 60}) ==
                    std::vector<int>{1, 1, 1, 0});
            REQUIRE(s.dailyTemperaturesDP({30, 40, 50, 60}) ==
                    std::vector<int>{1, 1, 1, 0});
        }

        SECTION("Example 3") {
            // Input: temperatures = [30,60,90]
            // Output: [1,1,0]
            Solution s;
            REQUIRE(s.dailyTemperatures({30, 60, 90}) ==
                    std::vector<int>{1, 1, 0});
            REQUIRE(s.dailyTemperaturesDP({30, 60, 90}) ==
                    std::vector<int>{1, 1, 0});
        }

        SECTION("Example 4") {
            Solution s;
            REQUIRE(s.dailyTemperatures(
                        {89, 62, 70, 58, 47, 47, 46, 76, 100, 70}) ==
                    std::vector<int>{8, 1, 5, 4, 3, 2, 1, 1, 0, 0});
            REQUIRE(s.dailyTemperaturesDP(
                        {89, 62, 70, 58, 47, 47, 46, 76, 100, 70}) ==
                    std::vector<int>{8, 1, 5, 4, 3, 2, 1, 1, 0, 0});
        }
    }
} // namespace P0739