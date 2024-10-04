#include <catch2/catch_test_macros.hpp>

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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        int carryover = 0;
        ListNode *result = new ListNode();
        ListNode *current = result;

        while (l1 || l2 || carryover) {
            int sum = 0;
            if (l1) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2) {
                sum += l2->val;
                l2 = l2->next;
            }
            sum += carryover;

            current->next = new ListNode(sum % 10);
            carryover = sum / 10;
            current = current->next;
        }
        return result->next;
    }
};

TEST_CASE("0002 - Add Two Numbers", "[Linked List][Math][Recursion]") {
    SECTION("Example 1") {
        Solution s;
        ListNode *l1 = new ListNode(2, new ListNode(4, new ListNode(3)));
        ListNode *l2 = new ListNode(5, new ListNode(6, new ListNode(4)));
        ListNode *result = s.addTwoNumbers(l1, l2);
        REQUIRE(result->val == 7);
        REQUIRE(result->next->val == 0);
        REQUIRE(result->next->next->val == 8);
    }

    SECTION("Example 2") {
        Solution s;
        ListNode *l1 = new ListNode(0);
        ListNode *l2 = new ListNode(0);
        const ListNode *result = s.addTwoNumbers(l1, l2);
        REQUIRE(result->val == 0);
    }

    SECTION("Example 3") {
        Solution s;
        ListNode *l1 = new ListNode(
            9,
            new ListNode(
                9, new ListNode(
                       9, new ListNode(
                              9, new ListNode(
                                     9, new ListNode(9, new ListNode(9)))))));
        ListNode *l2 =
            new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9))));
        ListNode *result = s.addTwoNumbers(l1, l2);
        REQUIRE(result->val == 8);
        REQUIRE(result->next->val == 9);
        REQUIRE(result->next->next->val == 9);
        REQUIRE(result->next->next->next->val == 9);
        REQUIRE(result->next->next->next->next->val == 0);
        REQUIRE(result->next->next->next->next->next->val == 0);
        REQUIRE(result->next->next->next->next->next->next->val == 0);
        REQUIRE(result->next->next->next->next->next->next->next->val == 1);
    }
}