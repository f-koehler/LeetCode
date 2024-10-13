#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <set>
#include <string>
#include <unordered_map>

/*
 * This class is for the follow-up questions, i.e. how to handle a lot of checks
 * against a single t. The idea is to build a lookup table of positions for each
 * character. Since, we will have a single lookup table per character we can
 * store them in an unordered map for efficient lookup. The lookup table for
 * each character is then a std::set (i.e. ordered). This allows us to check for
 * an occurence of a character after the current index in the t string in
 * O(log(n)).
 */
class IsSubsequenceCache {
  private:
    std::unordered_map<char, std::set<std::size_t>> m_positions;

  public:
    explicit IsSubsequenceCache(const std::string &t) {
        const std::size_t n = t.size();
        for (std::size_t i = 0; i < n; ++i) {
            const char c = t[i];
            if (auto pos = m_positions.find(c); pos != m_positions.end()) {
                // we already have a position set for character under
                // consideration -> insert it
                pos->second.insert(i);
                continue;
            }

            // we found a new character and create a new position set for its
            m_positions.insert({c, std::set<std::size_t>{i}});
        }
    }

    bool operator()(const std::string &s) const {

        // index in the target string t
        int64_t index = -1;

        for (const char c : s) {
            const auto c_positions = m_positions.find(c);

            // check if t contains the current character
            if (c_positions == m_positions.cend()) {
                // if not, s cannot be a subsequence
                return false;
            }

            // check if there is an occurence of c after the current index in t
            const auto earliest_c = c_positions->second.lower_bound(index + 1);
            if (earliest_c == c_positions->second.cend()) {
                return false;
            }

            // update index
            index = static_cast<int64_t>(*earliest_c);
        }

        return true;
    }
};

class Solution {
  public:
    bool isSubsequence(const std::string &s, const std::string &t) {
        auto iter_s = s.cbegin();
        auto iter_t = t.cbegin();
        while ((iter_s != s.cend()) && (iter_t != t.cend())) {
            if (*iter_s == *iter_t) {
                ++iter_s;
            }
            ++iter_t;
        }
        return iter_s == s.cend();
    }

    bool isSubsequenceCached(const std::string &s, const std::string &t) {
        // Of course this only really makes sense we check a lot of s's agains
        // the same t. This function is just to use the solution more easily on
        // LeetCode's platform.
        IsSubsequenceCache cache(t);
        return cache(s);
    }
};

TEST_CASE("0392 - Is Subsequence",
          "[Two Pointers][String][Dynamic Programming]") {
    Solution s;
    SECTION("Example 1") {
        REQUIRE(s.isSubsequence("abc", "ahbgdc"));
        REQUIRE(IsSubsequenceCache("ahbgdc")("abc"));
    }
    SECTION("Example 2") {
        REQUIRE(!s.isSubsequence("axc", "ahbgdc"));
        REQUIRE(!IsSubsequenceCache("ahbgdc")("axc"));
    }
}
