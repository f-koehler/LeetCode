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
            std::stack<std::pair<std::size_t, int>> stack;
            for (const auto [index, temperature] :
                 std::views::enumerate(temperatures)) {
                while (!stack.empty() && (temperature > stack.top().second)) {
                    result[stack.top().first] =
                        static_cast<int>(index - stack.top().first);
                    stack.pop();
                }
                stack.emplace(index, temperature);
            }
            return result;
        }
    };

    TEST_CASE("0739 - Daily Temperatures", "[Array][Stack][Monotonic Stack]") {

        SECTION("Example 1") {
            // Input: temperatures = [73,74,75,71,69,72,76,73]
            // Output: [1,1,4,2,1,1,0,0]
            Solution s;
            REQUIRE(s.dailyTemperatures({73, 74, 75, 71, 69, 72, 76, 73}) ==
                    std::vector<int>{1, 1, 4, 2, 1, 1, 0, 0});
        }

        SECTION("Example 2") {
            // Input: temperatures = [30,40,50,60]
            // Output: [1,1,1,0]
            Solution s;
            REQUIRE(s.dailyTemperatures({30, 40, 50, 60}) ==
                    std::vector<int>{1, 1, 1, 0});
        }

        SECTION("Example 3") {
            // Input: temperatures = [30,60,90]
            // Output: [1,1,0]
            Solution s;
            REQUIRE(s.dailyTemperatures({30, 60, 90}) ==
                    std::vector<int>{1, 1, 0});
        }

        SECTION("Example 4") {
            Solution s;
            REQUIRE(s.dailyTemperatures(
                        {89, 62, 70, 58, 47, 47, 46, 76, 100, 70}) ==
                    std::vector<int>{8, 1, 5, 4, 3, 2, 1, 1, 0, 0});
        }
    }
} // namespace P0739