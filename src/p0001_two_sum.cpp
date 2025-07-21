#include <catch2/catch_test_macros.hpp>
#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace P0001 {
    class Solution {
      public:
        std::vector<int> twoSum(const std::vector<int> &nums, int target) {
            std::unordered_map<int, int> seen{{nums[0], 0}};
            for (auto it = nums.begin() + 1; it != nums.end(); ++it) {
                const auto pos = seen.find(target - *it);
                if (pos != seen.end()) {
                    return {pos->second, static_cast<int>(it - nums.begin())};
                }
                seen.insert({*it, static_cast<int>(it - nums.begin())});
            }
            throw std::runtime_error("No solution");
        }
    };

    TEST_CASE("0001 - Two Sum", "[Arrays][Hash Table]") {
        SECTION("Example 1") {
            Solution s;
            std::vector<int> nums = {2, 7, 11, 15};
            REQUIRE(s.twoSum(nums, 9) == std::vector<int>({0, 1}));
        }
        SECTION("Example 2") {
            Solution s;
            std::vector<int> nums = {3, 2, 4};
            REQUIRE(s.twoSum(nums, 6) == std::vector<int>({1, 2}));
        }
        SECTION("Example 3") {
            Solution s;
            std::vector<int> nums = {3, 3};
            REQUIRE(s.twoSum(nums, 6) == std::vector<int>({0, 1}));
        }
    }
} // namespace P0001
