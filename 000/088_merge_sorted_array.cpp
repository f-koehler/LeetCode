#include <catch2/catch_test_macros.hpp>
#include <vector>

using namespace std;

class Solution {
  public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
        nums1.resize(m + n);

        int i = m - 1;
        int j = n - 1;
        while ((i >= 0) && (j >= 0)) {
            if (nums1[i] > nums2[j]) {
                nums1[i + j + 1] = nums1[i];
                --i;
            } else {
                nums1[i + j + 1] = nums2[j];
                --j;
            }
        }
        while (i >= 0) {
            nums1[i + j + 1] = nums1[i];
            --i;
        }
        while (j >= 0) {
            nums1[i + j + 1] = nums2[j];
            --j;
        }
    }
};

TEST_CASE("Merge Sorted Array", "[Arrays][Two Pointers][Sorting]") {
    SECTION("Example 1") {
        Solution s;
        vector<int> nums1 = {1, 2, 3, 0, 0, 0};
        vector<int> nums2 = {2, 5, 6};
        s.merge(nums1, 3, nums2, 3);
        REQUIRE(nums1 == vector<int>({1, 2, 2, 3, 5, 6}));
    }
    SECTION("Example 2") {
        Solution s;
        vector<int> nums1 = {1};
        vector<int> nums2 = {};
        s.merge(nums1, 1, nums2, 0);
        REQUIRE(nums1 == vector<int>({1}));
    }
    SECTION("Example 3") {
        Solution s;
        vector<int> nums1 = {0};
        vector<int> nums2 = {1};
        s.merge(nums1, 0, nums2, 1);
        REQUIRE(nums1 == vector<int>({1}));
    }
}