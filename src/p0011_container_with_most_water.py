class Solution:
    def maxArea(self, height: list[int]) -> int:
        assert len(height) > 1
        assert all(h >= 0 for h in height)
        left = 0
        right = len(height) - 1
        water = 0
        while left < right:
            water = max(water, min(height[left], height[right]) * (right - left))
            if height[left] < height[right]:
                left += 1
            else:
                right -= 1
        return water


def test_0011():
    s = Solution()

    # Example 1:
    # Input: height = [1,8,6,2,5,4,8,3,7]
    # Output: 49
    assert s.maxArea([1, 8, 6, 2, 5, 4, 8, 3, 7]) == 49

    # Example 2:
    # Input: height = [1,1]
    # Output: 1
    assert s.maxArea([1, 1]) == 1

    # Example 3
    # Input: height = [8,7,2,1]
    # Output: 7
    assert s.maxArea([8, 7, 2, 1]) == 7
