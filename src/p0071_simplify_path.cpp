#include <catch2/catch_test_macros.hpp>

#include <deque>
#include <string>
#include <string_view>

namespace LeetCode::P0071 {
    class Solution {
      public:
        [[nodiscard]] static std::string
        simplifyPath(const std::string &path_str) {
            const std::size_t size = path_str.size();
            std::string_view path(path_str);

            std::deque<std::string_view> components;
            std::size_t pos = 0;
            while (pos < size) {
                std::size_t separator_position = path.find('/', pos + 1);
                std::string_view component =
                    path.substr(pos + 1, separator_position - pos - 1);
                pos = separator_position;
                if (component.empty() || (component == ".")) {
                    continue;
                }
                if (component == "..") {
                    if (!components.empty()) {
                        components.pop_back();
                    }
                    continue;
                }
                components.push_back(component);
            }

            std::string result;
            result.reserve(path.size() + 1); // +1 for potential trailing slash (which gets removed afterwards)
            result.push_back('/');
            for (auto &component : components) {
                result.insert(result.size(), component);
                result.push_back('/');
            }
            if ((result.size() > 1) && result.back() == '/') {
                result.pop_back();
            }
            return result;
        }
    };

    TEST_CASE("0071 - Simplify Path", "[String][Stack]") {
        SECTION("Additional Cases") {
            REQUIRE(Solution::simplifyPath("/") == "/");
            REQUIRE(Solution::simplifyPath("/.") == "/");
        }
        SECTION("Example 1") {
            REQUIRE(Solution::simplifyPath("/home/") == "/home");
        }
        SECTION("Example 2") {
            REQUIRE(Solution::simplifyPath("/home//foo/") == "/home/foo");
        }
        SECTION("Example 3") {
            REQUIRE(
                Solution::simplifyPath("/home/user/Documents/../Pictures") ==
                "/home/user/Pictures");
        }
        SECTION("Example 4") { REQUIRE(Solution::simplifyPath("/../") == "/"); }
        SECTION("Example 4") {
            REQUIRE(Solution::simplifyPath("/.../a/../b/c/../d/./") ==
                    "/.../b/d");
        }
    }
} // namespace LeetCode::P0071
