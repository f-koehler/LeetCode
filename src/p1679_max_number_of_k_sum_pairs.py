class Solution:
    def maxOperations(self, nums: list[int], k: int) -> int:
        counts = {}
        result = 0
        for x in nums:
            if counts.get(k - x, 0) > 0:
                counts[k - x] -= 1
                result += 1
            else:
                counts[x] = counts.get(x, 0) + 1
        return result


def test_1679():
    s = Solution()

    # Example 1:
    # Input: nums = [1,2,3,4], k = 5
    # Output: 2
    assert s.maxOperations([1, 2, 3, 4], 5) == 2

    # Example 2:
    # Input: nums = [3,1,3,4,3], k = 6
    # Output: 1
    assert s.maxOperations([3, 1, 3, 4, 3], 6) == 1
