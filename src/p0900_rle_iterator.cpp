#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P0900 {
    class RLEIterator {
      private:
        std::vector<int> m_encoding;
        std::size_t m_index;
        std::size_t m_length;

      public:
        RLEIterator(const std::vector<int> &encoding)
            : m_encoding(encoding),
              m_index(0),
              m_length(encoding.size()) {}

        int next(int n) {
            while ((m_index < m_length) && (m_encoding[m_index] < n)) {
                n -= m_encoding[m_index];
                m_index += 2;
            }

            if (m_index == m_encoding.size()) {
                return -1;
            }

            m_encoding[m_index] -= n;
            return m_encoding[m_index + 1];
        }
    };

    /**
     * Your RLEIterator object will be instantiated and called as such:
     * RLEIterator* obj = new RLEIterator(encoding);
     * int param_1 = obj->next(n);
     */

    TEST_CASE("0900 - RLE Iterator", "[Array][Design][Counting][Iterator]") {
        RLEIterator iter({3, 8, 0, 9, 2, 5});
        REQUIRE(iter.next(2) == 8);
        REQUIRE(iter.next(1) == 8);
        REQUIRE(iter.next(1) == 5);
        REQUIRE(iter.next(2) == -1);
    }
} // namespace P0900
