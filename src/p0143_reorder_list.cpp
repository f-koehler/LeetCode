#include <catch2/catch_test_macros.hpp>
#include <tuple>
#include <utility>

namespace P0143 {
    struct ListNode {
        int val;
        ListNode *next;
        ListNode()
            : val(0),
              next(nullptr) {}
        ListNode(int x)
            : val(x),
              next(nullptr) {}
        ListNode(int x, ListNode *next)
            : val(x),
              next(next) {}
    };

    class Solution {
      public:
        ListNode *findSecondHalf(ListNode *head) {
            ListNode *slow_pointer = head;
            ListNode *fast_pointer = head;

            while ((fast_pointer->next != nullptr) &&
                   (fast_pointer->next->next != nullptr)) {
                slow_pointer = slow_pointer->next;
                fast_pointer = fast_pointer->next->next;
            }

            return slow_pointer;
        }

        ListNode *reverseRange(ListNode *begin, ListNode *end) {
            if (begin == end) {
                return begin;
            }

            ListNode *previous = end;
            ListNode *current = begin;
            while (current != end) {
                ListNode *next = current->next;
                current->next = previous;
                previous = current;
                current = next;
            }
            return previous;
        }

        void reorderList(ListNode *head) {
            if ((head == nullptr) || (head->next == nullptr)) {
                return;
            }

            // find second half of list
            ListNode *pre_second_half = findSecondHalf(head);
            ListNode *second_half_head = pre_second_half->next;

            // disconnect first half from second half
            pre_second_half->next = nullptr;

            // reverse second half of list
            second_half_head = reverseRange(second_half_head, nullptr);

            // merge two list
            ListNode *current_first_half = head;
            ListNode *current_second_half = second_half_head;

            while (current_second_half != nullptr) {
                // store next node for each half to not lose reference to it
                ListNode *next_first_half = current_first_half->next;
                ListNode *next_second_half = current_second_half->next;

                current_first_half->next = current_second_half;
                current_second_half->next = next_first_half;

                current_first_half = next_first_half;
                current_second_half = next_second_half;
            }
        }
    };

    TEST_CASE("0143 - Reorder List",
              "[Linked List][Two Pointers][Stack][Recursion]") {

        SECTION("Example 1 - Find Second Half") {
            Solution s;
            ListNode *node1 = new ListNode(1);
            ListNode *node2 = new ListNode(2);
            ListNode *node3 = new ListNode(3);
            ListNode *node4 = new ListNode(4);
            node1->next = node2;
            node2->next = node3;
            node3->next = node4;

            const auto pre_begin = s.findSecondHalf(node1);
            REQUIRE(pre_begin == node2);
            REQUIRE(pre_begin->next == node3);
            REQUIRE(pre_begin->next->next == node4);
            REQUIRE(pre_begin->next->next->next == nullptr);

            delete node4;
            delete node3;
            delete node2;
            delete node1;
        }

        SECTION("Example 2 - Find Second Half") {
            Solution s;
            ListNode *node1 = new ListNode(1);
            ListNode *node2 = new ListNode(2);
            ListNode *node3 = new ListNode(3);
            ListNode *node4 = new ListNode(4);
            ListNode *node5 = new ListNode(5);
            node1->next = node2;
            node2->next = node3;
            node3->next = node4;
            node4->next = node5;

            const auto pre_begin = s.findSecondHalf(node1);
            REQUIRE(pre_begin == node3);
            REQUIRE(pre_begin->next == node4);
            REQUIRE(pre_begin->next->next == node5);
            REQUIRE(pre_begin->next->next->next == nullptr);

            delete node5;
            delete node4;
            delete node3;
            delete node2;
            delete node1;
        }

        SECTION("Example 2 - Reverse First Three") {
            Solution s;
            ListNode *node1 = new ListNode(1);
            ListNode *node2 = new ListNode(2);
            ListNode *node3 = new ListNode(3);
            ListNode *node4 = new ListNode(4);
            ListNode *node5 = new ListNode(5);
            node1->next = node2;
            node2->next = node3;
            node3->next = node4;
            node4->next = node5;

            const auto *head = s.reverseRange(node1, node4);
            REQUIRE(head->val == 3);
            REQUIRE(head->next->val == 2);
            REQUIRE(head->next->next->val == 1);
            REQUIRE(head->next->next->next->val == 4);
            REQUIRE(head->next->next->next->next->val == 5);

            delete node5;
            delete node4;
            delete node3;
            delete node2;
            delete node1;
        }

        SECTION("Example 2 - Reverse Last Two") {
            Solution s;
            ListNode *node1 = new ListNode(1);
            ListNode *node2 = new ListNode(2);
            ListNode *node3 = new ListNode(3);
            ListNode *node4 = new ListNode(4);
            ListNode *node5 = new ListNode(5);
            node1->next = node2;
            node2->next = node3;
            node3->next = node4;
            node4->next = node5;

            ListNode *head = node1;
            node3->next = s.reverseRange(node4, nullptr);
            REQUIRE(head->val == 1);
            REQUIRE(head->next->val == 2);
            REQUIRE(head->next->next->val == 3);
            REQUIRE(head->next->next->next->val == 5);
            REQUIRE(head->next->next->next->next->val == 4);

            delete node5;
            delete node4;
            delete node3;
            delete node2;
            delete node1;
        }

        SECTION("Example 2 - Reverse All") {
            Solution s;
            ListNode *node1 = new ListNode(1);
            ListNode *node2 = new ListNode(2);
            ListNode *node3 = new ListNode(3);
            ListNode *node4 = new ListNode(4);
            ListNode *node5 = new ListNode(5);
            node1->next = node2;
            node2->next = node3;
            node3->next = node4;
            node4->next = node5;

            ListNode *head = s.reverseRange(node1, nullptr);
            REQUIRE(head->val == 5);
            REQUIRE(head->next->val == 4);
            REQUIRE(head->next->next->val == 3);
            REQUIRE(head->next->next->next->val == 2);
            REQUIRE(head->next->next->next->next->val == 1);

            delete node5;
            delete node4;
            delete node3;
            delete node2;
            delete node1;
        }

        SECTION("Example 1") {
            // Input: head = [1,2,3,4]
            // Output: [1,4,2,3]
            Solution s;
            ListNode *node1 = new ListNode(1);
            ListNode *node2 = new ListNode(2);
            ListNode *node3 = new ListNode(3);
            ListNode *node4 = new ListNode(4);
            node1->next = node2;
            node2->next = node3;
            node3->next = node4;

            s.reorderList(node1);
            REQUIRE(node1->val == 1);
            REQUIRE(node1->next->val == 4);
            REQUIRE(node1->next->next->val == 2);
            REQUIRE(node1->next->next->next->val == 3);

            delete node4;
            delete node3;
            delete node2;
            delete node1;
        }

        SECTION("Example 2") {
            // Input: head = [1,2,3,4,5]
            // Output: [1,5,2,4,3]
            Solution s;
            ListNode *node1 = new ListNode(1);
            ListNode *node2 = new ListNode(2);
            ListNode *node3 = new ListNode(3);
            ListNode *node4 = new ListNode(4);
            ListNode *node5 = new ListNode(5);
            node1->next = node2;
            node2->next = node3;
            node3->next = node4;
            node4->next = node5;

            s.reorderList(node1);
            REQUIRE(node1->val == 1);
            REQUIRE(node1->next->val == 5);
            REQUIRE(node1->next->next->val == 2);
            REQUIRE(node1->next->next->next->val == 4);
            REQUIRE(node1->next->next->next->next->val == 3);

            delete node5;
            delete node4;
            delete node3;
            delete node2;
            delete node1;
        }
    }
} // namespace P0143
