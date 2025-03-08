#include <catch2/catch_test_macros.hpp>
#include <deque>

namespace P0933 {
    class RecentCounter {
      private:
        std::deque<int> m_recents;

      public:
        RecentCounter() {}

        int ping(int t) {
            while (!m_recents.empty() && (m_recents.front() + 3000 < t)) {
                m_recents.pop_front();
            }
            m_recents.push_back(t);
            return m_recents.size();
        }
    };

    TEST_CASE("0933 - Number of Recent Calls", "[Design][Queue][Data Stream]") {
        SECTION("Example 1") {
            RecentCounter counter;
            REQUIRE(counter.ping(1) == 1);
            REQUIRE(counter.ping(100) == 2);
            REQUIRE(counter.ping(3001) == 3);
            REQUIRE(counter.ping(3002) == 3);
        }
    }
} // namespace P0933