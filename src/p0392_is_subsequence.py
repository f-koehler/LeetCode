import bisect


class Solution:
    def isSubsequence(self, s: str, t: str) -> bool:
        n_s = len(s)
        n_t = len(t)
        i = 0
        j = 0
        while (i < n_s) and (j < n_t):
            if s[i] == t[j]:
                i += 1
            j += 1
        return i == n_s


# For follow-up question, see explanation in C++ code
class CachedSolution:
    def __init__(self, t: str):
        self.positions: dict[str, list[int]] = {}
        for i, c in enumerate(t):
            indices = self.positions.get(c, [])
            indices.append(i)
            self.positions[c] = indices

    def __call__(self, s: str):
        i = -1
        for c in s:
            if c not in self.positions:
                return False

            indices = self.positions[c]
            # very sad that python does not have such a nice ordered set as C++
            j = bisect.bisect_right(indices, i)
            if j == len(indices):
                return False
            i = indices[j]
        return True


def test_0392_is_subsequence():
    s = Solution()

    assert s.isSubsequence("abc", "ahbgdc")
    assert CachedSolution("ahbgdc")("abc")
    assert not s.isSubsequence("axc", "ahbgdc")
    assert not CachedSolution("ahbgdc")("axc")
    assert not s.isSubsequence("acb", "ahbgdc")
    assert not CachedSolution("ahbgdc")("acb")
