#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P0056 {
    class Solution {
      public:
        std::vector<std::vector<int>>
        merge(std::vector<std::vector<int>> &intervals) {
            // vectors are compared lexicographically if they are of equal
            // length
            std::ranges::sort(intervals);

            const std::size_t num_intervals = intervals.size();
            std::vector<std::vector<int>> result;
            result.reserve(intervals.size());
            result.push_back(intervals.front());
            for (std::size_t i = 1; i < num_intervals; ++i) {
                const auto &interval = intervals[i];
                auto &current_interval = result.back();
                if (interval.front() <= current_interval.back()) {
                    // merge with last interval in result
                    //
                    // std::min important in case interval is completely
                    // contained in current_interval, do not make it shorter
                    current_interval.back() =
                        std::max(interval.back(), current_interval.back());
                    continue;
                }

                // start a new interval
                result.push_back(interval);
            }

            return result;
        }
    };

    TEST_CASE("0056 - Merge Intervals", "[Array][Sorting]") {

        SECTION("Example 1") {
            // Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
            // Output: [[1,6],[8,10],[15,18]]
            Solution s;
            std::vector<std::vector<int>> input{
                {1, 3}, {2, 6}, {8, 10}, {15, 18}};
            const std::vector<std::vector<int>> expected{
                {1, 6}, {8, 10}, {15, 18}};
            REQUIRE(s.merge(input) == expected);
        }

        SECTION("Example 2") {
            // Input: intervals = [[1,4],[4,5]]
            // Output: [[1,5]]
            Solution s;
            std::vector<std::vector<int>> input{{1, 4}, {4, 5}};
            const std::vector<std::vector<int>> expected{{1, 5}};
            REQUIRE(s.merge(input) == expected);
        }

        SECTION("Example 3") {
            // Input: intervals = [[1,4],[2,3]]
            // Output: [[1,4]]
            Solution s;
            std::vector<std::vector<int>> input{{1, 4}, {2, 3}};
            const std::vector<std::vector<int>> expected{{1, 4}};
            REQUIRE(s.merge(input) == expected);
        }
    }
} // namespace P0056
