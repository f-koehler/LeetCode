#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P0605 {
    class Solution {
      public:
        bool canPlaceFlowers(const std::vector<int> &flowerbed, int n) {
            const std::size_t size = flowerbed.size();
            if (n == 0) {
                return true;
            }
            if ((size == 1) && (n == 1)) {
                return flowerbed.front() == 0;
            }

            bool previous_occupied = false;
            for (std::size_t i = 0; i < size; ++i) {
                if (flowerbed[i]) {
                    previous_occupied = true;
                    continue;
                }

                if (previous_occupied) {
                    previous_occupied = false;
                    continue;
                }

                if ((i + 1 == size) || (!flowerbed[i + 1])) {
                    --n;
                    previous_occupied = true;
                }
            }

            return n <= 0;
        }
    };

    TEST_CASE("0605 - Can Place Flowers", "[Array][Greedy]") {
        Solution s;
        SECTION("Example 1") {
            std::vector<int> flowerbed{1, 0, 0, 0, 1};
            REQUIRE(s.canPlaceFlowers(flowerbed, 1));
        }
        SECTION("Example 2") {
            std::vector<int> flowerbed{1, 0, 0, 0, 1};
            REQUIRE(!s.canPlaceFlowers(flowerbed, 2));
        }
        SECTION("Example 3") {
            std::vector<int> flowerbed{0, 0, 1, 0, 1};
            REQUIRE(s.canPlaceFlowers(flowerbed, 1));
        }
        SECTION("Example 4") {
            std::vector<int> flowerbed{0, 0};
            REQUIRE(!s.canPlaceFlowers(flowerbed, 2));
        }
    }
} // namespace P0605