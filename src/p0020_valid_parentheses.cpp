#include <catch2/catch_test_macros.hpp>
#include <stack>
#include <string>

namespace LeetCode::P0020 {
    class Solution {
      public:
        [[nodiscard]] static bool isValid(const std::string &str)
            pre(!str.empty() && (str.size() <= 10000)) {
            std::stack<char> open;
            for (const char symbol : str) {
                contract_assert((symbol == '(') || (symbol == '[') ||
                                (symbol == '{') || (symbol == '}') ||
                                (symbol == ']') || (symbol == ')'));
                switch (symbol) {
                case '(':
                case '{':
                case '[':
                    open.push(symbol);
                    break;
                case ')':
                    if (open.empty() || (open.top() != '(')) {
                        return false;
                    }
                    open.pop();
                    continue;
                case '}':
                    if (open.empty() || (open.top() != '{')) {
                        return false;
                    }
                    open.pop();
                    continue;
                default:
                    if (open.empty() || (open.top() != '[')) {
                        return false;
                    }
                    open.pop();
                    continue;
                }
            }
            return open.empty();
        }
    };

    TEST_CASE("0020 - Valid Parentheses", "[String][Stack]") {
        SECTION("Example 1") { REQUIRE(Solution::isValid("()")); }
        SECTION("Example 2") { REQUIRE(Solution::isValid("()[]{}")); }
        SECTION("Example 3") { REQUIRE(!Solution::isValid("(]")); }
        SECTION("Example 4") { REQUIRE(Solution::isValid("([])")); }
        SECTION("Example 5") { REQUIRE(!Solution::isValid("([)]")); }
    }
} // namespace LeetCode::P0020
