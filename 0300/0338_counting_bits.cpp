#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P0338 {
    class Solution {
      public:
        std::vector<int> countBits(int n) {
            std::vector<int> result(n + 1, 0);
            if (n == 0) {
                return result;
            }

            // Dynamic programming approach: start with the list [0,1]
            // For each number i, we can do a bitshift by one to get the number
            // with the right-most bit removed for which we already know the
            // number of set bits. If i is even, its last bit is 0 otherwise it
            // is one. So we just need to add +1 if i is odd.
            result[1] = 1;
            for (int i = 2; i <= n; ++i) {
                result[i] = result[i >> 1] + (i % 2);
            }

            return result;
        }
    };

    TEST_CASE("0338 - Counting Bits",
              "[Dynamic Programming][Bit Manipulation]") {
        Solution s;
        SECTION("Example 1") {
            REQUIRE(s.countBits(2) == std::vector<int>{0, 1, 1});
        }
        SECTION("Example 2") {
            REQUIRE(s.countBits(5) == std::vector<int>{0, 1, 1, 2, 1, 2});
        }
    }
} // namespace P0338
