class Solution:
    def longestCommonPrefix(self, strs: list[str]) -> str:
        if len(strs) == 1:
            return strs[0]
        length = len(min(strs, key=len))
        for i in range(length):
            for j in range(1, len(strs)):
                if strs[j][i] != strs[0][i]:
                    return strs[0][:i]
        return strs[0][:length]


def test_0014():
    s = Solution()

    # Example 1:
    # Input: strs = ["flower","flow","flight"]
    # Output: "fl"
    assert s.longestCommonPrefix(["flower", "flow", "flight"]) == "fl"

    # Example 2:
    # Input: strs = ["dog","racecar","car"]
    # Output: ""
    assert s.longestCommonPrefix(["dog", "racecar", "car"]) == ""
