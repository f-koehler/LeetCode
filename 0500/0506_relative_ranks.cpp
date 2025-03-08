#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

namespace P0506 {
    /*
     * The priority queue/heap based approach hash a complexity O(n) when using
     * an efficient heap construction algorithm (heapify such as Floyd's
     * Build-Heap). The lookup of the top element then happens in constant time.
     *
     * For reasonably small arrays, the sorting algorithm will still perform
     * better despite its O(n log(n)) complexity.
     */
    class Solution {
      public:
        std::vector<std::string> findRelativeRanks(std::vector<int> &score) {
            const auto comparator = [&score](const std::size_t &a,
                                             const std::size_t &b) {
                return score[a] < score[b];
            };
            std::vector<std::size_t> indices(score.size());
            std::iota(indices.begin(), indices.end(), 0);
            std::priority_queue<std::size_t, std::vector<std::size_t>,
                                decltype(comparator)>
                pq{comparator, indices};
            std::vector<std::string> result(score.size());
            result.reserve(score.size());
            std::size_t counter = 0;
            while (!pq.empty()) {
                const std::size_t index = pq.top();
                if (counter > 2) {
                    result[index] = std::to_string(counter + 1);
                } else if (counter == 2) {
                    result[index] = "Bronze Medal";
                } else if (counter == 1) {
                    result[index] = "Silver Medal";
                } else {
                    result[index] = "Gold Medal";
                }
                pq.pop();
                ++counter;
            }
            return result;
        }

        std::vector<std::string>
        findRelativeRanksSorting(std::vector<int> &score) {
            std::vector<std::size_t> indices(score.size());
            std::iota(indices.begin(), indices.end(), 0);
            std::sort(indices.begin(), indices.end(),
                      [&score](const std::size_t &a, const std::size_t &b) {
                          return score[a] > score[b];
                      });
            std::vector<std::string> result(score.size());
            std::size_t counter = 0;

            for (const std::size_t &index : indices) {
                if (counter > 2) {
                    result[index] = std::to_string(counter + 1);
                } else if (counter == 2) {
                    result[index] = "Bronze Medal";
                } else if (counter == 1) {
                    result[index] = "Silver Medal";
                } else {
                    result[index] = "Gold Medal";
                }
                ++counter;
            }

            return result;
        }
    };

    TEST_CASE("0506 - Relative Ranks", "[Array][Sorting][Heap]") {
        Solution s;
        SECTION("Example 1") {
            std::vector<int> input{5, 4, 3, 2, 1};
            std::vector<std::string> output{"Gold Medal", "Silver Medal",
                                            "Bronze Medal", "4", "5"};

            REQUIRE(s.findRelativeRanks(input) == output);
            REQUIRE(s.findRelativeRanksSorting(input) == output);
        }
        SECTION("Example 2") {
            std::vector<int> input{10, 3, 8, 9, 4};
            std::vector<std::string> output{
                "Gold Medal", "5", "Bronze Medal", "Silver Medal", "4",
            };
            REQUIRE(s.findRelativeRanks(input) == output);
            REQUIRE(s.findRelativeRanksSorting(input) == output);
        }
    }
} // namespace P0506
