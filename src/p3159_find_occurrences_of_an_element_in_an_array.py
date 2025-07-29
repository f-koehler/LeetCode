class Solution:
    def occurrencesOfElement(
        self, nums: list[int], queries: list[int], x: int
    ) -> list[int]:
        occurences = [i for i, val in enumerate(nums) if val == x]
        num_occurences = len(occurences)
        return [occurences[q - 1] if q <= num_occurences else -1 for q in queries]


def test_3159():
    s = Solution()
    assert s.occurrencesOfElement([1, 3, 1, 7], [1, 3, 2, 4], 1) == [0, -1, 2, -1]
    assert s.occurrencesOfElement([1, 2, 3], [10], 5) == [-1]
