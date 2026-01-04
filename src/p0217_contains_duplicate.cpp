#include <catch2/catch_test_macros.hpp>
#include <unordered_set>
#include <vector>

namespace P0217 {
    class Solution {
      public:
        [[nodiscard]] bool containsDuplicate(const std::vector<int> &nums) {
            std::unordered_set<int> unique_numbers;
            for (const int num : nums) {
                if (unique_numbers.contains(num)) {
                    return true;
                }
                unique_numbers.insert(num);
            }
            return false;
        }
    };

    TEST_CASE("0217 - Contains Duplicate",
              "[Array][Hash Table][Sorting][NeetCode150]") {
        SECTION("Example 1") {
            REQUIRE(Solution().containsDuplicate({1, 2, 3, 1}));
        }
        SECTION("Example 2") {
            REQUIRE(!Solution().containsDuplicate({1, 2, 3, 4}));
        }
        SECTION("Example 3") {
            REQUIRE(Solution().containsDuplicate({1,1,1,3,3,4,3,2,4,2}));
        }
    }
} // namespace P0217