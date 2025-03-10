class Solution:
    def longestOnes(self, nums: list[int], k: int) -> int:
        left = 0
        right = 0
        max_length = 0
        n = len(nums)

        while right < n:
            if nums[right] == 0:
                k -= 1

            while k < 0:
                if nums[left] == 0:
                    k += 1
                left += 1

            right += 1
            max_length = max(max_length, right - left)

        return max_length


def test_1004():
    s = Solution()

    # Example 1:
    # Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
    # Output: 6
    assert s.longestOnes([1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0], 2) == 6

    # Example 2:
    # Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
    # Output: 10
    assert (
        s.longestOnes([0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1], 3)
        == 10
    )
