#include <catch2/catch_test_macros.hpp>
#include <deque>

namespace P0155 {
    class MinStack {

        /**
         * std::deque is the proper choice for this datastructure over
         * std::vector:
         *
         * - Like std::vector it supports efficient lookup of the last element
         * (top of our stack)
         * - It can grow dynamically (we are only pushing elements on the
         * stack). This would cause a lot of re-allocations in std::vector, we
         * are not pre-allocating a known capacity.
         */
        std::deque<int> m_values;

        // Auxiliary stack that stores the min value as the stack grows. Add the
        // cost of a lot of complexity we could save memory using some
        // run-length-encoding for the case that the minimum does not change
        // very often.
        std::deque<int> m_min_values;

      public:
        MinStack() {}

        void push(int val) {
            m_values.push_back(val);
            if (m_min_values.empty()) {
                m_min_values.push_back(val);
            } else {
                m_min_values.push_back(std::min(val, m_min_values.back()));
            }
        }

        void pop() {
            // we are guarantee that this is not called on empty stack
            m_values.pop_back();
            m_min_values.pop_back();
        }

        int top() {
            // we are guarantee that this is not called on empty stack
            return m_values.back();
        }

        int getMin() { return m_min_values.back(); }
    };

    /**
     * Your MinStack object will be instantiated and called as such:
     * MinStack* obj = new MinStack();
     * obj->push(val);
     * obj->pop();
     * int param_3 = obj->top();
     * int param_4 = obj->getMin();
     */

    TEST_CASE("0155 - Min Stack", "[Stack][Design]") {
        MinStack stack;
        stack.push(-2);
        stack.push(0);
        stack.push(-3);
        REQUIRE(stack.getMin() == -3);
        stack.pop();
        REQUIRE(stack.top() == 0);
        REQUIRE(stack.getMin() == -2);
    }
} // namespace P0155
