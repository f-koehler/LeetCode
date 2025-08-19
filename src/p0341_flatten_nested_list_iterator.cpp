#include <catch2/catch_test_macros.hpp>
#include <deque>
#include <vector>

namespace P0341 {
    /**
     * // This is the interface that allows for creating nested lists.
     * // You should not implement it, or speculate about its implementation
     * class NestedInteger {
     *   public:
     *     // Return true if this NestedInteger holds a single integer, rather
     * than a nested list. bool isInteger() const;
     *
     *     // Return the single integer that this NestedInteger holds, if it
     * holds a single integer
     *     // The result is undefined if this NestedInteger holds a nested list
     *     int getInteger() const;
     *
     *     // Return the nested list that this NestedInteger holds, if it holds
     * a nested list
     *     // The result is undefined if this NestedInteger holds a single
     * integer const vector<NestedInteger> &getList() const;
     * };
     */

    class NestedInteger {
      private:
        bool m_is_integer;
        int m_integer;
        std::vector<NestedInteger> m_list;

      public:
        NestedInteger(int integer)
            : m_is_integer(true),
              m_integer(integer) {}
        NestedInteger(std::vector<NestedInteger> &&list)
            : m_is_integer(false),
              m_list(std::move(list)) {}

        [[nodiscard]] constexpr bool isInteger() const noexcept {
            return m_is_integer;
        }
        [[nodiscard]] constexpr int getInteger() const noexcept {
            return m_integer;
        }
        [[nodiscard]] constexpr const std::vector<NestedInteger> &
        getList() const noexcept {
            return m_list;
        }
    };

    class NestedIterator {
      private:
        std::deque<int> m_flattened_list;
        std::size_t m_index;
        std::size_t m_length;

        void flattenList(const std::vector<NestedInteger> &nestedList) {
            for (const auto &element : nestedList) {
                if (element.isInteger()) {
                    m_flattened_list.push_back(element.getInteger());
                    continue;
                }

                flattenList(element.getList());
            }
        }

      public:
        NestedIterator(const std::vector<NestedInteger> &nestedList)
            : m_index(0) {
            flattenList(nestedList);
            m_length = m_flattened_list.size();
        }

        int next() { return m_flattened_list[m_index++]; }

        bool hasNext() { return m_index < m_length; }
    };

    /**
     * Your NestedIterator object will be instantiated and called as such:
     * NestedIterator i(nestedList);
     * while (i.hasNext()) cout << i.next();
     */

    TEST_CASE("0341 - Flatten Nested List Iterator",
              "[Stack][Tree][Depth-First Search][Design][Queue][Iterator]") {

        SECTION("Example 1") {
            // Input: nestedList = [[1,1],2,[1,1]]
            // Output: [1,1,2,1,1]
            NestedIterator iter = NestedIterator(
                {NestedInteger({NestedInteger(1), NestedInteger(1)}),
                 NestedInteger(2),
                 NestedInteger({NestedInteger(1), NestedInteger(1)})});
            REQUIRE(iter.hasNext());
            REQUIRE(iter.next() == 1);
            REQUIRE(iter.hasNext());
            REQUIRE(iter.next() == 1);
            REQUIRE(iter.hasNext());
            REQUIRE(iter.next() == 2);
            REQUIRE(iter.hasNext());
            REQUIRE(iter.next() == 1);
            REQUIRE(iter.hasNext());
            REQUIRE(iter.next() == 1);
            REQUIRE(!iter.hasNext());
        }

        SECTION("Example 2") {
            // Input: nestedList = [1,[4,[6]]]
            // Output: [1,4,6]
            NestedIterator iter = NestedIterator(
                {NestedInteger(1),
                 NestedInteger({NestedInteger(4), NestedInteger({
                                                      NestedInteger(6),
                                                  })})});
            REQUIRE(iter.hasNext());
            REQUIRE(iter.next() == 1);
            REQUIRE(iter.hasNext());
            REQUIRE(iter.next() == 4);
            REQUIRE(iter.hasNext());
            REQUIRE(iter.next() == 6);
            REQUIRE(!iter.hasNext());
        }
    }
} // namespace P0341
