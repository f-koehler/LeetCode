#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace P0284 {
    /*
     * Below is the interface for Iterator, which is already defined for you.
     * **DO NOT** modify the interface for Iterator.
     *
     *  class Iterator {
     *		struct Data;
     * 		Data* data;
     *  public:
     *		Iterator(const vector<int>& nums);
     * 		Iterator(const Iterator& iter);
     *
     * 		// Returns the next element in the iteration.
     *		int next();
     *
     *		// Returns true if the iteration has more elements.
     *		bool hasNext() const;
     *	};
     */
    class Iterator {
      private:
        const int *m_data;
        std::size_t m_index;
        std::size_t m_size;

      public:
        Iterator(const std::vector<int> &nums)
            : m_data(nums.data()),
              m_index(0),
              m_size(nums.size()) {}
        Iterator(const Iterator &iter)
            : m_data(iter.m_data),
              m_index(iter.m_index),
              m_size(iter.m_size) {}

        // Returns the next element in the iteration.
        int next() { return m_data[m_index++]; }

        // Returns true if the iteration has more elements.
        bool hasNext() const { return (m_index + 1) < m_size; }
    };

    class PeekingIterator : public Iterator {
      public:
        PeekingIterator(const std::vector<int> &nums)
            : Iterator(nums) {
            // Initialize any member here.
            // **DO NOT** save a copy of nums and manipulate it directly.
            // You should only use the Iterator interface methods.
        }

        // Returns the next element in the iteration without advancing the
        // iterator.
        int peek() {
            // create a temporary iterator and return its next element
            //
            // leaves the current iterator unchanged
            return Iterator(*this).next();
        }

        // hasNext() and next() should behave the same as in the Iterator
        // interface. Override them if needed.
        int next() { return Iterator::next(); }

        bool hasNext() const { return Iterator::hasNext(); }
    };

    TEST_CASE("0284 - Peeking Iterator", "[Array][Design][Iterator]") {
        std::vector<int> nums{1, 2, 3};
        PeekingIterator iter(nums);
        REQUIRE(iter.next() == 1);
        REQUIRE(iter.peek() == 2);
        REQUIRE(iter.next() == 2);
        REQUIRE(iter.next() == 3);
        REQUIRE(!iter.hasNext());
    }
} // namespace P0284
