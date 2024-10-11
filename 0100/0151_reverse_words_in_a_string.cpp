#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <string>

class Solution {
  public:
    std::string reverseWords(const std::string &s) {
        std::istringstream in(s);
        std::string word;
        std::string result;
        word.reserve(s.size());
        result.reserve(s.size());
        while (in >> word) {
            std::reverse(word.begin(), word.end());
            if (!result.empty()) {
                result.push_back(' ');
            }
            result += word;
        }

        // result now contains the original word order with each word spelled
        // backwards -> we can reverse the whole string
        std::reverse(result.begin(), result.end());
        return result;
    }

    std::string &reverseWordsInPlace(std::string &s) {
        // remove duplicate whitespaces
        bool space_before = true;
        s.erase(std::remove_if(s.begin(), s.end(),
                               [&space_before](char c) {
                                   if (c == ' ') {
                                       if (space_before) {
                                           return true;
                                       }
                                       space_before = true;
                                       return false;
                                   }
                                   space_before = false;
                                   return false;
                               }),
                s.end());

        // remove potential trailing whitespace
        if (s.back() == ' ') {
            s.pop_back();
        }

        // reverse whole string -> each word will be spelled backwards
        std::reverse(s.begin(), s.end());

        // reverse each word
        std::size_t word_begin = 0;
        std::size_t word_end = s.find(' ', 0);
        while (word_end != std::string::npos) {
            std::reverse(s.begin() + word_begin, s.begin() + word_end);
            word_begin = word_end + 1;
            word_end = s.find(' ', word_begin);
        }
        std::reverse(s.begin() + word_begin, s.end()); // reverse last word

        return s;
    }
};

TEST_CASE("0151 - Reverse Words in a String", "[Two Pointers][String]") {
    Solution s;
    SECTION("Example 1") {
        REQUIRE(s.reverseWords("the sky is blue") == "blue is sky the");
        std::string input = "the sky is blue";
        REQUIRE(s.reverseWordsInPlace(input) == "blue is sky the");
    }
    SECTION("Example 2") {
        REQUIRE(s.reverseWords("  hello world  ") == "world hello");
        std::string input = "  hello world  ";
        REQUIRE(s.reverseWordsInPlace(input) == "world hello");
    }
    SECTION("Example 3") {
        REQUIRE(s.reverseWords("a good   example") == "example good a");
        std::string input = "a good   example";
        REQUIRE(s.reverseWordsInPlace(input) == "example good a");
    }
}