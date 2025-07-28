#include <catch2/catch_test_macros.hpp>
#include <unordered_map>
#include <vector>

namespace P3160 {
    class Solution {
      public:
        std::vector<int>
        queryResults(int /* limit  */,
                     const std::vector<std::vector<int>> &queries) {
            const std::size_t num_queries = queries.size();
            std::vector<int> result;
            result.reserve(num_queries);

            std::unordered_map<int, int> ball_color;
            std::unordered_map<int, int> color_count;

            for (const auto &query : queries) {
                const int ball = query[0];
                const int color = query[1];

                ++color_count[color];

                // check if ball is already colored
                auto pos = ball_color.find(ball);

                // check if ball already has a color
                if (pos != ball_color.end()) {
                    // check if it is the last ball with that color
                    const int current_color = pos->second;
                    if (--color_count[current_color] == 0) {
                        // remove the color from the count map so that we can
                        // determine the number of distinct colors using size()
                        color_count.erase(current_color);
                    }

                    // update ball to new color
                    pos->second = color;
                } else {
                    // insert ball with an initial color
                    ball_color.insert({ball, color});
                }

                result.push_back(color_count.size());
            }

            return result;
        }
    };

    TEST_CASE("3160 - Find the Number of Distinct Colors Among the Balls",
              "[Array][Hash Table][Simulation]") {
        SECTION("Example 1") {
            Solution s;
            REQUIRE(s.queryResults(4, {{1, 4}, {2, 5}, {1, 3}, {3, 4}}) ==
                    std::vector<int>{1, 2, 2, 3});
        }
        SECTION("Example 2") {
            Solution s;
            REQUIRE(
                s.queryResults(4, {{0, 1}, {1, 2}, {2, 2}, {3, 4}, {4, 5}}) ==
                std::vector<int>{1, 2, 2, 3, 4});
        }
    }
} // namespace P3160
