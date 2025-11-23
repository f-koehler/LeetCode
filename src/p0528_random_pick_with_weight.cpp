#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <cstdlib>
#include <numeric>
#include <random>

namespace P0528 {
    class Solution {
      private:
        std::vector<int64_t> m_partial_sum;
        std::default_random_engine m_generator;
        std::uniform_int_distribution<int64_t> m_distribution;

      public:
        Solution(const std::vector<int> &w)
            : m_partial_sum(w.size(), 0.0) {
            std::partial_sum(w.cbegin(), w.cend(), m_partial_sum.begin());

            // minus 1 so that we cannot get an beyond end iterator
            m_distribution = std::uniform_int_distribution<int64_t>(
                0, m_partial_sum.back() - 1);
        }

        int pickIndex() {
            return std::distance(
                m_partial_sum.begin(),
                std::ranges::upper_bound(m_partial_sum,
                                         m_distribution(m_generator)));
        }
    };

    /**
     * Your Solution object will be instantiated and called as such:
     * Solution* obj = new Solution(w);
     * int param_1 = obj->pickIndex();
     */

    TEST_CASE("0528 - Random Pick with Weight",
              "[Array][Math][Binary Search][Prefix Sum][Randomized]") {
        Solution solution({1, 3});
        int index = solution.pickIndex();
        REQUIRE(index >= 0);
        REQUIRE(index < 2);

        // Ensure the index is picked according to the weights
        int count[2] = {0, 0};
        for (int i = 0; i < 1000000; ++i) {
            index = solution.pickIndex();
            count[index]++;
        }
        // failure is very unlikely
        REQUIRE(count[0] + count[1] == 1000000);
        REQUIRE(count[0] < count[1]);
        REQUIRE(std::abs(static_cast<double>(count[0]) /
                             static_cast<double>(count[0] + count[1]) -
                         0.25) < 0.01);
    }
} // namespace P0528
