#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <queue>
#include <ranges>
#include <set>

namespace P1606 {
    struct RunningJob {
        int server;
        int stop_time;
        auto operator<=>(const RunningJob &other) const {
            return stop_time <=> other.stop_time;
        }
        bool operator==(const RunningJob &other) const {
            return (server == other.server) && (stop_time == other.stop_time);
        }
    };
    class Solution {
      public:
        std::vector<int> busiestServers(int k, const std::vector<int> &arrival,
                                        const std::vector<int> &load) {
            std::vector<int> num_jobs_handled(k, 0);

            // not supported by LeetCode yet:
            // std::set<int> idle_servers(std::from_range,
            //                            std::ranges::views::iota(0, k));
            std::set<int> idle_servers;
            for (auto i : std::ranges::views::iota(0, k)) {
                idle_servers.insert(i);
            }

            std::priority_queue<RunningJob, std::vector<RunningJob>,
                                std::greater<RunningJob>>
                running_jobs;

            for (auto [i, a, l] : std::ranges::views::zip(
                     std::ranges::views::iota(0), arrival, load)) {
                const int time = a - 1;
                // pop completed jobs and mark corresponding servers as idle
                while (!running_jobs.empty() &&
                       (running_jobs.top().stop_time <= time)) {
                    idle_servers.insert(running_jobs.top().server);
                    running_jobs.pop();
                }

                // drop job if there are no idle servers
                if (idle_servers.empty()) {
                    continue;
                }

                // find first idle server from i%k onwards
                auto pos = idle_servers.lower_bound(i % k);
                if (pos == idle_servers.end()) {
                    // if not found, use first server from 0 onwards
                    pos = idle_servers.begin();
                }
                const int chosen_server = *pos;

                // schedule job on chosen server
                idle_servers.erase(pos);
                running_jobs.emplace(chosen_server, time + l);
                ++num_jobs_handled[chosen_server];
            }

            const int max_jobs_handled = *std::max_element(
                num_jobs_handled.cbegin(), num_jobs_handled.cend());

            std::vector<int> result;
            result.reserve(k);
            for (auto [server, num_jobs] :
                 std::ranges::views::enumerate(num_jobs_handled)) {
                if (num_jobs == max_jobs_handled) {
                    result.push_back(server);
                }
            }
            return result;
        }
    };

    TEST_CASE("1606 - Find Servers That Handled Most Number of Requests",
              "[Array][Greedy][Heap (Priority Queue)][Ordered Set]") {

        SECTION("Example 1") {
            // Input: k = 3, arrival = [1,2,3,4,5], load = [5,2,3,3,3]
            // Output: [1]
            Solution s;
            auto result = s.busiestServers(3, {1, 2, 3, 4, 5}, {5, 2, 3, 3, 3});
            std::ranges::sort(result);
            REQUIRE(result == std::vector<int>{1});
        }

        SECTION("Example 2") {
            // Input: k = 3, arrival = [1,2,3,4], load = [1,2,1,2]
            // Output: [0]
            Solution s;
            auto result = s.busiestServers(3, {1, 2, 3, 4}, {1, 2, 1, 2});
            std::ranges::sort(result);
            REQUIRE(result == std::vector<int>{0});
        }

        SECTION("Example 3") {
            // Input: k = 3, arrival = [1,2,3], load = [10,12,11]
            // Output: [0,1,2]
            Solution s;
            auto result = s.busiestServers(3, {1, 2, 3}, {10, 12, 11});
            std::ranges::sort(result);
            REQUIRE(result == std::vector<int>{0, 1, 2});
        }
    }
} // namespace P1606
