#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <numeric>
#include <vector>
using Catch::Matchers::WithinRel;

class Solution {
  public:
    double findMaxAverage(const std::vector<int> &nums, int k) {
        double current_average =
            std::accumulate(nums.cbegin(), nums.cbegin() + k, 0.0) /
            static_cast<double>(k);
        double max_average = current_average;

        for (auto begin = nums.cbegin(), next = nums.cbegin() + k;
             (begin != nums.cend()) && (next != nums.cend()); ++begin, ++next) {
            current_average = ((current_average * k) - *begin + *next) / k;
            max_average = std::max(current_average, max_average);
        }
        return max_average;
    }
};

TEST_CASE("0643 - Maximum Average Subarray I", "[Array][Sliding Window]") {
    Solution s;
    SECTION("Example 1") {
        REQUIRE_THAT(
            s.findMaxAverage(std::vector<int>{1, 12, -5, -6, 50, 3}, 4),
            WithinRel(12.75, 1e-5));
    }
    SECTION("Example 2") {
        REQUIRE_THAT(s.findMaxAverage(std::vector<int>{5}, 1),
                     WithinRel(5.0, 1e-5));
    }
}
