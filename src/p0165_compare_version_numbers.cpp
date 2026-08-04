#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <charconv>
#include <cstdint>
#include <string>

namespace LeetCode::P0165 {
    class Solution {
      public:
        [[nodiscard]] static int compareVersion(const std::string &version1,
                                                const std::string &version2) {
            std::size_t token_begin1 = 0;
            std::size_t token_begin2 = 0;
            while ((token_begin1 < version1.size()) ||
                   (token_begin2 < version2.size())) {
                uint64_t component1 = 0;
                if (token_begin1 < version1.size()) {
                    std::size_t token_end1 = std::min(
                        version1.size(), version1.find('.', token_begin1));
                    std::from_chars(version1.c_str() + token_begin1,
                                    version1.c_str() + token_end1, component1);
                    token_begin1 = token_end1 + 1;
                }

                uint64_t component2 = 0;
                if (token_begin2 < version2.size()) {
                    std::size_t token_end2 = std::min(
                        version2.size(), version2.find('.', token_begin2));
                    std::from_chars(version2.c_str() + token_begin2,
                                    version2.c_str() + token_end2, component2);
                    token_begin2 = token_end2 + 1;
                }
                if (component1 < component2) {
                    return -1;
                }
                if (component1 > component2) {
                    return 1;
                }
            }
            return 0;
        }
    };

    TEST_CASE("0165 - Compare Version Numbers", "[Two Pointers][String]") {
        SECTION("Example 1") {
            REQUIRE(Solution::compareVersion("1.2", "1.10") == -1);
        }
        SECTION("Example 2") {
            REQUIRE(Solution::compareVersion("1.01", "1.001") == 0);
        }
        SECTION("Example 3") {
            REQUIRE(Solution::compareVersion("1.0", "1.0.0.0") == 0);
        }
    }
} // namespace LeetCode::P0165
