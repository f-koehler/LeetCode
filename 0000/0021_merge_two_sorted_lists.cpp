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
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
        if (!list1)
            return list2;
        if (!list2)
            return list1;

        ListNode *new_list = list1;
        if (list1->val > list2->val) {
            new_list = list2;
            list2 = list2->next;
        } else {
            list1 = list1->next;
        }

        ListNode *current = new_list;
        while (list1 && list2) {
            if (list1->val > list2->val) {
                current->next = list2;
                list2 = list2->next;
            } else {
                current->next = list1;
                list1 = list1->next;
            }
            current = current->next;
        }
        while (list1) {
            current->next = list1;
            list1 = list1->next;
            current = current->next;
        }
        while (list2) {
            current->next = list2;
            list2 = list2->next;
            current = current->next;
        }

        return new_list;
    }
};

TEST_CASE("0021 - Merge Two Sorted Lists", "[Linked List][Recursion]") {
    SECTION("Example 1") {
        Solution s;

        ListNode *list1 = new ListNode(1);
        list1->next = new ListNode(2);
        list1->next->next = new ListNode(4);

        ListNode *list2 = new ListNode(1);
        list2->next = new ListNode(3);
        list2->next->next = new ListNode(4);

        ListNode *result = s.mergeTwoLists(list1, list2);
        REQUIRE(result->val == 1);
        REQUIRE(result->next->val == 1);
        REQUIRE(result->next->next->val == 2);
        REQUIRE(result->next->next->next->val == 3);
        REQUIRE(result->next->next->next->next->val == 4);
        REQUIRE(result->next->next->next->next->next->val == 4);
    }

    SECTION("Example 2") {
        Solution s;
        ListNode *list1 = nullptr;
        ListNode *list2 = nullptr;
        ListNode *result = s.mergeTwoLists(list1, list2);
        REQUIRE(result == nullptr);
    }

    SECTION("Example 3") {
        Solution s;
        ListNode *list1 = nullptr;
        ListNode *list2 = new ListNode(0);
        ListNode *result = s.mergeTwoLists(list1, list2);
        REQUIRE(result->val == 0);
    }
}