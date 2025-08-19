#include <algorithm>
#include <bit>
#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <ranges>
#include <string>

namespace P1286 {
    class CombinationIterator {
      private:
        const uint64_t m_length;
        const std::string m_alphabet;
        const std::size_t m_alphabet_size;
        uint64_t m_current_mask;
        std::string m_buffer;

      public:
        CombinationIterator(const std::string &characters,
                            int combinationLength)
            : m_length(combinationLength),
              m_alphabet(characters),
              m_alphabet_size(characters.size()),
              m_current_mask((1 << characters.size()) - 1) {
            m_buffer.reserve(m_length);
        }

        std::string next() {
            // go to next valid combination
            while ((m_current_mask > 0) && (static_cast<uint64_t>(std::popcount(
                                                m_current_mask)) != m_length)) {
                --m_current_mask;
            }

            m_buffer.clear();
            // unfortunately, LeetCode does not have std::views::enumerate yet
            for (std::size_t alphabet_index = 0;
                 alphabet_index < m_alphabet_size; ++alphabet_index) {
                // MSB of mask => first character in alphabet
                const uint64_t mask_index =
                    m_alphabet_size - alphabet_index - 1;
                if ((m_current_mask >> mask_index) & 1UL) {
                    m_buffer.push_back(m_alphabet[alphabet_index]);
                }
            }

            --m_current_mask;
            return m_buffer;
        }

        bool hasNext() {
            // go to next valid combination
            while ((m_current_mask > 0) && (static_cast<uint64_t>(std::popcount(
                                                m_current_mask)) != m_length)) {
                --m_current_mask;
            }

            return m_current_mask > 0;
        }
    };

    /**
     * Your CombinationIterator object will be instantiated and called as
     * such: CombinationIterator* obj = new CombinationIterator(characters,
     * combinationLength); string param_1 = obj->next(); bool param_2 =
     * obj->hasNext();
     */

    TEST_CASE("1286 - Iterator for Combination",
              "[String][Backtracking][Design][Iterator]") {
        SECTION("Example 1") {
            CombinationIterator iter("abc", 2);
            REQUIRE(iter.next() == "ab");
            REQUIRE(iter.hasNext());
            REQUIRE(iter.next() == "ac");
            REQUIRE(iter.hasNext());
            REQUIRE(iter.next() == "bc");
            REQUIRE(!iter.hasNext());
        }
        SECTION("Example 2") {
            CombinationIterator iter("bvwz", 2);
            REQUIRE(iter.hasNext());
            REQUIRE(iter.hasNext());
            REQUIRE(iter.next() == "bv");
            REQUIRE(iter.next() == "bw");
            REQUIRE(iter.hasNext());
            REQUIRE(iter.hasNext());
            REQUIRE(iter.next() == "bz");
            REQUIRE(iter.hasNext());
            REQUIRE(iter.hasNext());
            REQUIRE(iter.hasNext());
        }
    }
} // namespace P1286
