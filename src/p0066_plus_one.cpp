#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P0066 {
    class Solution {
      public:
        std::vector<int> plusOne(std::vector<int> &digits) {
            const int n = static_cast<int>(digits.size());
            for (int i = n - 1; i >= 0; --i) {
                digits[i] = (digits[i] + 1) % 10;
                if (digits[i] != 0) {
                    return digits;
                }
            }
            digits.insert(digits.begin(), 1);
            return digits;
        }
    };

    TEST_CASE("0066 - Plus One", "[Array][Math][NeetCode150]") {

        SECTION("Example 1") {
            // Input: digits = [1,2,3]
            // Output: [1,2,4]
            std::vector<int> digits{1, 2, 3};
            Solution{}.plusOne(digits);
            REQUIRE(digits == std::vector<int>{1, 2, 4});
        }

        SECTION("Example 2") {
            // Input: digits = [4,3,2,1]
            // Output: [4,3,2,2]
            std::vector<int> digits{4, 3, 2, 1};
            Solution{}.plusOne(digits);
            REQUIRE(digits == std::vector<int>{4, 3, 2, 2});
        }

        SECTION("Example 3") {
            // Input: digits = [9]
            // Output: [1,0]
            std::vector<int> digits{9};
            Solution{}.plusOne(digits);
            REQUIRE(digits == std::vector<int>{1, 0});
        }
    }
} // namespace P0066