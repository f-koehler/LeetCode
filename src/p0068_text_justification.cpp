#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>

namespace LeetCode::P0068 {
    class Solution {
      public:
        [[nodiscard]] static std::vector<std::string>
        fullJustify(const std::vector<std::string> &words,
                    std::size_t max_width) {
            std::vector<std::string> result;

            std::size_t num_words = words.size();
            std::size_t word_index = 0;
            while (word_index < num_words) {
                // put first word in new line
                std::vector<std::string> line_words{words[word_index]};
                std::size_t line_length = words[word_index].size();
                ++word_index;

                // add words as long as we stay below max_width (including
                // mandatory spaces)
                while (
                    (word_index < num_words) &&
                    (line_length + words[word_index].size() + 1 <= max_width)) {
                    line_words.push_back(words[word_index]);
                    line_length += 1 + words[word_index].size();
                    ++word_index;
                }

                // finalize line
                std::string line;
                line.reserve(max_width);

                // line with one word and last line should be left-aligned
                if ((line_words.size() == 1) || (word_index == num_words)) {
                    line += line_words.front();
                    for (std::size_t i = 1; i < line_words.size(); ++i) {
                        line.push_back(' ');
                        line += line_words[i];
                    }
                    // insert padding on the right
                    line.insert(line.size(), max_width - line.size(), ' ');
                    result.emplace_back(std::move(line));
                    continue;
                }

                // normal line should be justified
                const std::size_t word_pairs = line_words.size() - 1;
                const std::size_t word_characters = line_length - word_pairs;
                const std::size_t total_spaces = max_width - word_characters;
                const std::size_t base_spaces =
                    total_spaces /
                    word_pairs; // number of spaces between every word pair
                const std::size_t extra_spaces =
                    total_spaces %
                    word_pairs; // number of extra spaces to distribute from the
                                // left to the right (remainder)
                for (std::size_t i = 0; i < line_words.size() - 1; ++i) {
                    line += line_words[i];
                    int spaces_to_add =
                        base_spaces + ((i < extra_spaces) ? 1 : 0);
                    line.insert(line.size(), spaces_to_add, ' ');
                }
                line += line_words.back();

                result.emplace_back(std::move(line));
            }

            return result;
        }
    };

    TEST_CASE("0068 - Text Justification", "[Array][String][Simulation]") {
        SECTION("Example 1") {
            REQUIRE(Solution::fullJustify({"This", "is", "an", "example", "of",
                                           "text", "justification."},
                                          16) == std::vector<std::string>{
                                                     "This    is    an",
                                                     "example  of text",
                                                     "justification.  ",
                                                 });
        }
        SECTION("Example 2") {
            REQUIRE(Solution::fullJustify(
                        {"What", "must", "be", "acknowledgment", "shall", "be"},
                        16) == std::vector<std::string>{
                                   "What   must   be",
                                   "acknowledgment  ",
                                   "shall be        ",
                               });
        }

        SECTION("Example 3") {
            REQUIRE(Solution::fullJustify(
                        {"Science", "is", "what", "we", "understand", "well",
                         "enough", "to", "explain", "to", "a", "computer.",
                         "Art", "is", "everything", "else", "we", "do"},
                        20) == std::vector<std::string>{
                                   "Science  is  what we",
                                   "understand      well",
                                   "enough to explain to",
                                   "a  computer.  Art is",
                                   "everything  else  we",
                                   "do                  ",
                               });
        }
    }
} // namespace LeetCode::P0068
