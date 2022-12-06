#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <string>
using namespace std;

class Solution {
  public:
    string reverseWords(string s) {
        auto word_start = s.begin();
        auto word_end = s.begin();
        while (word_end != s.end()) {
            ++word_end;
            if (*word_end == ' ') {
                std::reverse(word_start, word_end);
                ++word_end;
                word_start = word_end;
            }
        }
        if (word_start < word_end) {
            std::reverse(word_start, word_end);
        }
        return s;
    }
};

TEST_CASE("0557 - Reverse Words in a String III", "[Two Pointers][String]") {
    Solution s;
    REQUIRE(s.reverseWords("Let's take LeetCode contest") ==
            "s'teL ekat edoCteeL tsetnoc");
    REQUIRE(s.reverseWords("God Ding") == "doG gniD");
}