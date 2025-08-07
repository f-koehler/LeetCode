#include <catch2/catch_test_macros.hpp>
#include <ranges>
#include <set>

namespace P1606 {
    class Solution {
      public:
        std::vector<int> busiestServers(int k, const std::vector<int> &arrival,
                                        const std::vector<int> &load) {
            std::vector<int> num_jobs_handled(k, 0);
            std::set<int> idle_servers;
            for (auto [i, a, l] :
                 std::views::zip(std::views::iota(0), arrival, load)) {
            }
        }
    };

    TEST_CASE("1606 - Find Servers That Handled Most Number of Requests",
              "[Array][Greedy][Heap (Priority Queue)][Ordered Set]") {

        SECTION("Example 1") {
            // Input: k = 3, arrival = [1,2,3,4,5], load = [5,2,3,3,3]
            // Output: [1]
            Solution s;
        }

        SECTION("Example 2") {
            // Input: k = 3, arrival = [1,2,3,4], load = [1,2,1,2]
            // Output: [0]
            Solution s;
        }

        SECTION("Example 3") {
            // Input: k = 3, arrival = [1,2,3], load = [10,12,11]
            // Output: [0,1,2]
            Solution s;
        }
    }
} // namespace P1606
