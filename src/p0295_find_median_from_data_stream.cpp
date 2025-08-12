#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <functional>
#include <iostream>
#include <print>
#include <queue>
#include <vector>

namespace P0295 {
    class MedianFinder {
      private:
        // min heap to hold the larger half of elements encountered thus far ->
        // fast retrieval of the smallest element of the larger half of elements
        std::priority_queue<int, std::deque<int>, std::greater<int>> m_min_heap;

        // max heap to hold the small half of elements encountered thus far ->
        // fast retrieval of the largest element of the smaller half of elements
        std::priority_queue<int, std::deque<int>, std::less<int>> m_max_heap;

      public:
        MedianFinder() {}

        void addNum(int num) {
            // insert new number into the max_heap (smallest elements)
            m_max_heap.push(num);

            // move the largest element to the min_heap
            m_min_heap.push(m_max_heap.top());
            m_max_heap.pop();

            // make sure the heaps remain balanced
            if (m_max_heap.size() < m_min_heap.size() - 1) {
                m_max_heap.push(m_min_heap.top());
                m_min_heap.pop();
            }
        }

        double findMedian() {
            if (m_min_heap.size() == m_max_heap.size()) {
                // both heaps are of equal size -> encountered an even number of
                // elements
                return static_cast<double>(m_min_heap.top() +
                                           m_max_heap.top()) /
                       2.;
            }

            // median element is the smallest element of the min heap (large
            // elements) otherwise
            return static_cast<double>(m_min_heap.top());
        }
    };

    /**
     * Your MedianFinder object will be instantiated and called as such:
     * MedianFinder* obj = new MedianFinder();
     * obj->addNum(num);
     * double param_2 = obj->findMedian();
     */

    TEST_CASE(
        "0295 - Find Median from Data Stream",
        "[Two Pointers][Design][Sorting][Heap (Priority Queue)][Data Stream]") {
        SECTION("Example 1") {
            MedianFinder finder;
            finder.addNum(1);
            finder.addNum(2);
            REQUIRE_THAT(finder.findMedian(),
                         Catch::Matchers::WithinULP(1.5, 1));
            finder.addNum(3);
            REQUIRE_THAT(finder.findMedian(),
                         Catch::Matchers::WithinULP(2.0, 1));
        }
        SECTION("Example 2") {
            MedianFinder finder;
            finder.addNum(-1);
            REQUIRE_THAT(finder.findMedian(),
                         Catch::Matchers::WithinULP(-1.0, 1));
            finder.addNum(-2);
            REQUIRE_THAT(finder.findMedian(),
                         Catch::Matchers::WithinULP(-1.5, 1));
            finder.addNum(-3);
            REQUIRE_THAT(finder.findMedian(),
                         Catch::Matchers::WithinULP(-2.0, 1));
            finder.addNum(-4);
            REQUIRE_THAT(finder.findMedian(),
                         Catch::Matchers::WithinULP(-2.5, 1));
            finder.addNum(-5);
            REQUIRE_THAT(finder.findMedian(),
                         Catch::Matchers::WithinULP(-3.0, 1));
        }
    }
} // namespace P0295
