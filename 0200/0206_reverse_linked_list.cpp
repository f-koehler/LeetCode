#include <catch2/catch_test_macros.hpp>

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
    ListNode *reverseList(ListNode *head) {
        ListNode *previous = nullptr;
        ListNode *current = head;
        ListNode *tmp = nullptr;

        while (current) {
            tmp = current->next;
            current->next = previous;
            previous = current;
            current = tmp;
        }

        return previous;
    }
};

TEST_CASE("0206 - Reverse Linked List", "[Reverse Linked List]") {
    SECTION("Example 1") {
        Solution s;

        ListNode *head = new ListNode(1);
        head->next = new ListNode(2);
        head->next->next = new ListNode(3);
        head->next->next->next = new ListNode(4);
        head->next->next->next->next = new ListNode(5);

        ListNode *result = s.reverseList(head);
        REQUIRE(result->val == 5);
        REQUIRE(result->next->val == 4);
        REQUIRE(result->next->next->val == 3);
        REQUIRE(result->next->next->next->val == 2);
        REQUIRE(result->next->next->next->next->val == 1);
    }

    SECTION("Example 2") {
        Solution s;

        ListNode *head = new ListNode(1);
        head->next = new ListNode(2);

        ListNode *result = s.reverseList(head);
        REQUIRE(result->val == 2);
        REQUIRE(result->next->val == 1);
    }

    SECTION("Example 3") {
        Solution s;

        ListNode *head = new ListNode(1);
        ListNode *result = s.reverseList(head);
        REQUIRE(result->val == 1);
    }
}