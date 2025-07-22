from itertools import islice


class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        if not s:
            return 0

        start = 0
        characters = {s[0]: 0}
        max_length = 1

        for i, c in islice(enumerate(s), 1, None):
            if c in characters:
                max_length = max(max_length, i - start)

                duplicate_index = characters[c]
                for c2 in s[start : duplicate_index + 1]:
                    del characters[c2]

                start = duplicate_index + 1
            characters[c] = i

        max_length = max(max_length, len(s) - start)
        return max_length


def test_0003():
    s = Solution()

    # Example 1:
    # Input: s = "abcabcbb"
    # Output: 3
    assert s.lengthOfLongestSubstring("abcabcbb") == 3

    # Example 2:
    # Input: s = "bbbbb"
    # Output: 1
    assert s.lengthOfLongestSubstring("bbbbb") == 1

    # Example 3:
    # Input: s = "pwwkew"
    # Output: 3
    assert s.lengthOfLongestSubstring("pwwkew") == 3
