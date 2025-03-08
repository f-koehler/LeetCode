#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P0443 {
    class Solution {
      public:
        int compress(std::vector<char> &characters) {
            std::size_t destination = 0;

            for (std::size_t current = 0; current < characters.size();) {
                // start a new group with the current character
                const char character = characters[current];
                std::size_t group_length = 0;

                // increment i until we reach the end of the group (either the
                // end of the array or a different character)
                while ((current < characters.size()) &&
                       (characters[current] == character)) {
                    ++group_length;
                    ++current;
                }

                // Put correct letter at ouput position. Increment destination
                // as each group has at least one letter.
                characters[destination++] = character;

                if (group_length > 1) {
                    // More than one character in the group -> write group
                    // length
                    for (const char digit : std::to_string(group_length)) {
                        characters[destination++] = digit;
                    }
                }
            }

            // our new length is given by destination

            // make sure to remove trailing characters
            characters.resize(destination);
            return destination;
        }
    };

    TEST_CASE("0443 - String Compression", "[Two Pointers][String]") {
        Solution s;
        SECTION("Example 1") {
            std::vector<char> input = {'a', 'a', 'b', 'b', 'c', 'c', 'c'};
            REQUIRE(s.compress(input) == 6);
            REQUIRE(input == std::vector<char>{'a', '2', 'b', '2', 'c', '3'});
        }
        SECTION("Example 2") {
            std::vector<char> input = {'a'};
            REQUIRE(s.compress(input) == 1);
            REQUIRE(input == std::vector<char>{'a'});
        }
        SECTION("Example 3") {
            std::vector<char> input = {'a', 'b', 'b', 'b', 'b', 'b', 'b',
                                       'b', 'b', 'b', 'b', 'b', 'b'};
            REQUIRE(s.compress(input) == 4);
            REQUIRE(input == std::vector<char>{'a', 'b', '1', '2'});
        }
        SECTION("Example 4") {
            std::vector<char> input = {'a', 'a', 'a', 'b', 'b', 'a', 'a'};
            REQUIRE(s.compress(input) == 6);
            REQUIRE(input == std::vector<char>{'a', '3', 'b', '2', 'a', '2'});
        }
    }
} // namespace P0443
