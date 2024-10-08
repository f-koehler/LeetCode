#include <catch2/catch_test_macros.hpp>
#include <vector>

class Solution {
  public:
    std::vector<int> asteroidCollision(const std::vector<int> &asteroids) {
        // A stack based on a deque would be the ideal datastructure here.
        // However, we need to return a vector so we use that. There should be
        // no performance downside to this choice if we reserve the maximal
        // possible size of a stable row.
        std::vector<int> stable_row;
        stable_row.reserve(asteroids.size());

        for (const int &asteroid : asteroids) {
            const int size = -asteroid;

            while (true) {
                // The next asteroid does not cause a collision if one of these
                // conditions is met:
                // 1. It is the first asteroid in the row (either because we
                // start or all previous was have been destroyed).
                // 2. It is moving to the right.
                // 3. The last asteroid in the row is moving to the left.
                if (stable_row.empty() || asteroid > 0 ||
                    stable_row.back() < 0) {
                    stable_row.push_back(asteroid);
                    break;
                }

                // The asteroid is moving to the left and the last asteroid in
                // the stable row to the right -> collision.
                if (size > stable_row.back()) {
                    // destroy the last assteroid in the row
                    stable_row.pop_back();
                    continue;
                }

                if (size < stable_row.back()) {
                    // The new asteroid is destroyed by the last asteroid in the
                    // row.
                    break;
                }

                // The new asteroid and the last asteroid in the row are
                // destroyed due to their equal mass.
                stable_row.pop_back();
                break;
            }
        }
        return stable_row;
    }
};

TEST_CASE("735 - Asteroid Collision", "[Array][Stack][Simulation]") {
    Solution s;
    SECTION("Example 1") {
        REQUIRE(s.asteroidCollision(std::vector<int>{5, 10, -5}) ==
                std::vector<int>{5, 10});
    }
    SECTION("Example 2") {
        REQUIRE(s.asteroidCollision(std::vector<int>{8, -8}) ==
                std::vector<int>{});
    }
    SECTION("Example 3") {
        REQUIRE(s.asteroidCollision(std::vector<int>{10, 2, -5}) ==
                std::vector<int>{10});
    }
}