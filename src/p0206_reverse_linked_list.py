# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def reverseList(self, head: ListNode | None) -> ListNode | None:
        current = head
        previous = None

        while current:
            next = current.next
            current.next = previous
            previous = current
            current = next

        return previous


def test_0011():
    s = Solution()

    # Example 1
    head = s.reverseList(
        ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5, None)))))
    )
    assert head is not None
    assert head.val == 5
    assert head.next is not None
    assert head.next.val == 4
    assert head.next.next is not None
    assert head.next.next.val == 3
    assert head.next.next.next is not None
    assert head.next.next.next.val == 2
    assert head.next.next.next.next is not None
    assert head.next.next.next.next.val == 1
    assert head.next.next.next.next.next is None

    # Example 2
    head = s.reverseList(ListNode(1, ListNode(2, None)))
    assert head is not None
    assert head.val == 2
    assert head.next is not None
    assert head.next.val == 1
    assert head.next.next is None

    # Example 3
    assert s.reverseList(None) is None
