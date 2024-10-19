#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <deque>
#include <vector>

class Solution {
  public:
    bool canVisitAllRooms(const std::vector<std::vector<int>> &rooms) {
        const std::size_t num_rooms = rooms.size();
        std::vector<bool> visited(num_rooms, false);
        std::deque<std::size_t> next;
        next.push_back(0);
        std::size_t num_visited = 0;

        while (!next.empty()) {
            const std::size_t index = next.front();
            next.pop_front();

            if (visited[index]) {
                continue;
            }

            ++num_visited;
            visited[index] = true;
            if (num_visited == num_rooms) {
                return true;
            }
            std::copy_if(rooms[index].cbegin(), rooms[index].cend(),
                         std::back_inserter(next),
                         [&visited](int i) { return !visited[i]; });
        }

        return false;
    }
};

TEST_CASE("0841 - Keys and Rooms",
          "[Depth-First Search][Breadth-First Search][Graph]") {
    Solution s;
    SECTION("Example 1") {
        std::vector<std::vector<int>> rooms{{1}, {2}, {3}, {}};
        REQUIRE(s.canVisitAllRooms(rooms));
    }
    SECTION("Example 2") {
        std::vector<std::vector<int>> rooms{{1, 3}, {3, 0, 1}, {2}, {0}};
        REQUIRE(!s.canVisitAllRooms(rooms));
    }
}
