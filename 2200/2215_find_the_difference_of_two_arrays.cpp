#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <set>
#include <vector>

namespace P2215 {
    class Solution {
      public:
        std::vector<std::vector<int>>
        findDifference(const std::vector<int> &nums1,
                       const std::vector<int> &nums2) {
            std::vector<std::vector<int>> result{2};
            result[0].reserve(nums1.size());
            result[1].reserve(nums2.size());

            /*
             * std::set<> constructor: worst case O(N log N) (linear if nums1
             * would be sorted) std::unordered_set<> constructor: worst case
             * O(N^2), average case O(N)
             * -> using std::set<> has better asymptotic behavior, but
             * std::unordered_set<> can still be faster in practice (average
             * case)
             */
            std::set<int> set1(nums1.begin(), nums1.end());
            std::set<int> set2(nums2.begin(), nums2.end());

            // look up is O(N) in std::set<>, the runtime for the conversion is
            // thus O(N1 log(N2)) and O(N2 log(N1)) respectively
            // std::unorder_set<> lookup is O(N) in the worst case, constant on
            // average, the worst case total complexities would thus be O(N1 *
            // N2) for each conversion
            std::copy_if(set1.begin(), set1.end(),
                         std::back_inserter(result[0]),
                         [&set2](int n) { return !set2.contains(n); });
            std::copy_if(set2.begin(), set2.end(),
                         std::back_inserter(result[1]),
                         [&set1](int n) { return !set1.contains(n); });

            return result;
        }
    };

    TEST_CASE("2215 - Find the Difference of two Arrays",
              "[Array][Hash Table]") {
        Solution s;
        SECTION("Example 1") {
            std::vector<int> nums1{1, 2, 3};
            std::vector<int> nums2{2, 4, 6};

            auto result = s.findDifference(nums1, nums2);
            std::sort(result[0].begin(), result[0].end());
            std::sort(result[1].begin(), result[1].end());
            REQUIRE(result[0] == std::vector<int>{1, 3});
            REQUIRE(result[1] == std::vector<int>{4, 6});
        }
        SECTION("Example 2") {
            std::vector<int> nums1{1, 2, 3, 3};
            std::vector<int> nums2{1, 1, 2, 2};

            auto result = s.findDifference(nums1, nums2);
            std::sort(result[0].begin(), result[0].end());
            std::sort(result[1].begin(), result[1].end());
            REQUIRE(result[0] == std::vector<int>{3});
            REQUIRE(result[1] == std::vector<int>{});
        }
    }
} // namespace P2215