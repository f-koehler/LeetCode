#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <vector>

namespace P3159 {
    class Solution {
      public:
        std::vector<int> occurrencesOfElement(const std::vector<int> &nums,
                                              const std::vector<int> &queries,
                                              int x) {
            const std::size_t length = nums.size();

            // create an array of all occurrences of x in nums
            std::vector<std::size_t> occurence_indices;
            occurence_indices.reserve(length);
            for (std::size_t i = 0; i < length; ++i) {
                if (nums[i] == x) {
                    occurence_indices.push_back(i);
                }
            }
            const std::size_t num_occurences = occurence_indices.size();

            // we can simply apply each query to our occurence array
            //
            // careful: we have to subtract one from each query, a query value
            // of 1 corresponds to the first occurence
            const std::size_t num_queries = queries.size();
            std::vector<int> result(num_queries, -1);
            for (std::size_t i = 0; i < num_queries; ++i) {
                const int query = queries[i] - 1;
                if (static_cast<std::size_t>(query) < num_occurences) {
                    result[i] = occurence_indices[query];
                }
            }

            return result;
        }
    };

    TEST_CASE("3159 - Find Occurrences of an Element in an Array",
              "[Array][Hash Table]") {
        SECTION("Example 1") {
            Solution s;
            REQUIRE(s.occurrencesOfElement({1, 3, 1, 7}, {1, 3, 2, 4}, 1) ==
                    std::vector<int>{0, -1, 2, -1});
        }
        SECTION("Example 2") {
            Solution s;
            REQUIRE(s.occurrencesOfElement({1, 2, 3}, {10}, 5) ==
                    std::vector<int>{-1});
        }
    }
} // namespace P3159