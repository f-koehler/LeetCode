#include <catch2/catch_test_macros.hpp>
#include <iterator>
#include <string>

namespace P1768 {
    class Solution {
      public:
        std::string mergeAlternately(const std::string &word1,
                                     const std::string &word2) {
            std::string result;
            result.reserve(word1.size() + word2.size());
            auto iter1 = word1.cbegin();
            auto iter2 = word2.cbegin();
            while ((iter1 != word1.cend()) && (iter2 != word2.cend())) {
                result.push_back(*iter1);
                result.push_back(*iter2);
                ++iter1;
                ++iter2;
            }
            std::copy(iter1, word1.cend(), std::back_inserter(result));
            std::copy(iter2, word2.cend(), std::back_inserter(result));
            return result;
        }
    };

    TEST_CASE("1768 - Merge String Alternately", "[Two Pointers][String]") {
        Solution s;
        SECTION("Example 1") {
            REQUIRE(s.mergeAlternately("abc", "pqr") == "apbqcr");
        }
        SECTION("Example 2") {
            REQUIRE(s.mergeAlternately("ab", "pqrs") == "apbqrs");
        }
        SECTION("Example 3") {
            REQUIRE(s.mergeAlternately("abcd", "pq") == "apbqcd");
        }
    }
} // namespace P1768