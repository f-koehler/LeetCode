class Solution(object):
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """

        seen: dict[int, int] = {}
        for i, num in enumerate(nums):
            j = seen.get(target - num)
            if j is not None:
                return [j, i]

            seen[num] = i


def test_0001():
    s = Solution()

    # Example 1:
    assert s.twoSum([2, 7, 11, 15], 9) == [0, 1]

    # Example 2:
    assert s.twoSum([3, 2, 4], 6) == [1, 2]

    # Example 3:
    assert s.twoSum([3, 3], 6) == [0, 1]
