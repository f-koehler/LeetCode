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
    ListNode *middleNode(ListNode *head) {
        ListNode *slow = head;
        ListNode *fast = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
};

TEST_CASE("0876 - Middle of the Linked List", "[Linked List][Two Pointers]") {
    SECTION("Example 1") {
        ListNode *head = new ListNode(1);
        head->next = new ListNode(2);
        head->next->next = new ListNode(3);
        head->next->next->next = new ListNode(4);
        head->next->next->next->next = new ListNode(5);
        Solution s;
        REQUIRE(s.middleNode(head)->val == 3);
    }
    SECTION("Example 2") {
        ListNode *head = new ListNode(1);
        head->next = new ListNode(2);
        head->next->next = new ListNode(3);
        head->next->next->next = new ListNode(4);
        head->next->next->next->next = new ListNode(5);
        head->next->next->next->next->next = new ListNode(6);
        Solution s;
        REQUIRE(s.middleNode(head)->val == 4);
    }
}