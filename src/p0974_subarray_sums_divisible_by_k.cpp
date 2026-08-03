#include <catch2/catch_test_macros.hpp>
#include <unordered_map>
#include <vector>

namespace LeetCode::P0974 {
    class Solution {
      public:
        /**
         * Let P_i be the prefix sum up to i, i.e. P_i = ∑_{l=1}^i a_i. We are
         * then looking for start indices i and end indices j with:
         *    (P_j - P_{i-1}) = 0 mod k
         * ⇔ P_j = P_{i-1} mod k
         *
         * So we are looking for indices where the prefix sum have the same mod
         * k.
         *
         * One complication: negative numbers are allowed, e.g.: -2 % 5 is -2 to
         * and not three. We have to normalize: ((prefix % k) + k) % k is in the
         * range 0,...,k-1
         */
        [[nodiscard]] static int subarraysDivByK(const std::vector<int> &nums,
                                                 int k)
            pre(!nums.empty() && (k > 1)) {
            std::unordered_map<int, int> prefix_sum_frequency(nums.size());
            prefix_sum_frequency[0] = 1; // empty prefix

            int prefix_sum = 0;
            int result = 0;
            for (int num : nums) {
                prefix_sum += num;

                // compute the value of the startin prefix sum modulo k,
                // normalized to positive values
                int remainder = ((prefix_sum % k) + k) % k;

                // check how many previous prefix sums have the correct modulo
                result += prefix_sum_frequency[remainder];
                prefix_sum_frequency[remainder]++;
            }
            return result;
        }
    };

    TEST_CASE("0974 - Subarray Sums Divisible by K",
              "[Array][Hash Table][Prefix Sum]") {

        SECTION("Example 1") {
            // Input: nums = [4,5,0,-2,-3,1], k = 5
            // Output: 7
            REQUIRE(Solution::subarraysDivByK({4, 5, 0, -2, -3, 1}, 5) == 7);
        }

        SECTION("Example 2") {
            // Input: nums = [5], k = 9
            // Output: 0
            REQUIRE(Solution::subarraysDivByK({5}, 9) == 0);
        }
    }
} // namespace LeetCode::P0974
