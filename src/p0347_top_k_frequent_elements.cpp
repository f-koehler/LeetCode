#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <functional>
#include <queue>
#include <unordered_map>
#include <utility>

namespace LeetCode::P0347 {
    class Solution {
      public:
        [[nodiscard]] static std::vector<int>
        topKFrequent(const std::vector<int> &nums, const int k)
            pre(!nums.empty() && (nums.size() <= 100000) && (k > 0) &&
                (static_cast<std::size_t>(k) <= nums.size()))
                post(result : result.size() == static_cast<std::size_t>(k)) {
            // compute frequency of every number O(n)
            std::unordered_map<int, std::size_t> counts;
            for (const auto num : nums) {
                contract_assert((-10000 <= num) && (10000 >= num));
                ++counts[num];
            }

            // std::pair uses lexicographically ordering: the first element is
            // compared first (count)
            using ElementFrequency = std::pair<std::size_t, int>;

            // create a min queue (least frequent at the top/front)
            std::priority_queue<ElementFrequency, std::vector<ElementFrequency>,
                                std::greater<ElementFrequency>>
                most_frequent;

            // build a min heap with a size contraint of k
            for (const auto &[num, frequency] : counts) {
                most_frequent.emplace(ElementFrequency{frequency, num});
                if (most_frequent.size() > static_cast<std::size_t>(k)) {
                    most_frequent.pop();
                }
            }

            std::vector<int> result;
            result.reserve(k);
            while (!most_frequent.empty()) {
                result.push_back(most_frequent.top().second);
                most_frequent.pop();
            }
            return result;
        }
    };

    TEST_CASE("0347 - Top K Frequent Elements",
              "[Array][Hash Table][Divide and Conquer][Sorting][Heap (Priority "
              "Queue)][Bucket Sort][Counting][Quickselect]") {
        SECTION("Example 1") {
            auto result =
                Solution::topKFrequent(std::vector<int>{1, 1, 1, 2, 2, 3}, 2);
            std::ranges::sort(result);
            REQUIRE(result == std::vector<int>{1, 2});
        }
        SECTION("Example 2") {
            auto result = Solution::topKFrequent(std::vector<int>{1}, 1);
            std::ranges::sort(result);
            REQUIRE(result == std::vector<int>{1});
        }

        SECTION("Example 3") {
            auto result = Solution::topKFrequent(
                std::vector<int>{1, 2, 1, 2, 1, 2, 3, 1, 3, 2}, 2);
            REQUIRE(result == std::vector<int>{1, 2});
        }
    }
} // namespace LeetCode::P0347
