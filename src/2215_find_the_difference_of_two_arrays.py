class Solution:
    def findDifference(self, nums1: list[int], nums2: list[int]) -> list[list[int]]:
        # set -> would give O(N^2) worst case performance on construction
        # Python does not have a builtin OrderedSet
        # We can use a dict instead (which is ordered in Python 3.7+)
        # This will give a better asymptotic performance, however in practice a set can still be the better choice (e.g. for large inputs with few collisions when hashing)
        set1 = {n: None for n in nums1}
        print(set1)
        set2 = {n: None for n in nums2}
        print(set2)
        return [
            [n for n in set1 if n not in set2],
            [n for n in set2 if n not in set1],
        ]


def test_2216_find_the_difference_of_two_arrays():
    s = Solution()

    result = s.findDifference([1, 2, 3], [2, 4, 6])
    assert len(result[0]) == 2
    assert len(result[1]) == 2
    assert set(result[0]) == {1, 3}
    assert set(result[1]) == {4, 6}

    result = s.findDifference([1, 2, 3, 3], [1, 1, 2, 2])
    assert len(result[0]) == 1
    assert len(result[1]) == 0
    assert set(result[0]) == {3}
    assert set(result[1]) == set()
