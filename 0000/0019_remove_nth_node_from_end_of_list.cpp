#include <catch2/catch_test_macros.hpp>

namespace P0019 {
    struct ListNode {
        int val;
        ListNode *next;
        ListNode()
            : val(0),
              next(nullptr) {}
        explicit ListNode(int x)
            : val(x),
              next(nullptr) {}
        ListNode(int x, ListNode *next)
            : val(x),
              next(next) {}
    };

    class Solution {
      public:
        ListNode *removeNthFromEnd(ListNode *head, int n) {
            ListNode *tail = head;
            for (int i = 0; i < n; ++i) {
                tail = tail->next;
            }

            // handle the case that we now reached the end of list
            // i.e. we remove the head node
            if (!tail) {
                return head->next;
            }

            ListNode *before_target = head;
            while (tail->next) {
                tail = tail->next;
                before_target = before_target->next;
            }

            // skip element
            before_target->next = before_target->next->next;
            return head;
        }
    };

    TEST_CASE("0019 - Remove Nth Node From End of List",
              "[Linked List][Two Pointers]") {
        Solution s;
        SECTION("Example 1") {
            ListNode *head = new ListNode(
                1, new ListNode(
                       2, new ListNode(3, new ListNode(4, new ListNode(5)))));
            ListNode *result = s.removeNthFromEnd(head, 2);
            REQUIRE(result->val == 1);
            REQUIRE(result->next->val == 2);
            REQUIRE(result->next->next->val == 3);
            REQUIRE(result->next->next->next->val == 5);
            REQUIRE(result->next->next->next->next == nullptr);
        }
        SECTION("Example 2") {
            ListNode *head = new ListNode(1);
            const ListNode *result = s.removeNthFromEnd(head, 1);
            REQUIRE(result == nullptr);
        }
        SECTION("Example 3") {
            ListNode *head = new ListNode(1, new ListNode(2));
            const ListNode *result = s.removeNthFromEnd(head, 1);
            REQUIRE(result->val == 1);
            REQUIRE(result->next == nullptr);
        }
    }
} // namespace P0019