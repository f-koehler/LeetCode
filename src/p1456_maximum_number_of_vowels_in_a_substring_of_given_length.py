class Solution:
    def maxVowels(self, s: str, k: int) -> int:
        vowels = {"a", "e", "i", "o", "u"}

        num_vowels = sum(1 for c in s[:k] if c in vowels)
        max_vowels = num_vowels

        for i in range(len(s) - k):
            num_vowels -= s[i] in vowels
            num_vowels += s[i + k] in vowels
            max_vowels = max(max_vowels, num_vowels)

        return max_vowels


def test_1456():
    s = Solution()

    # Example 1:
    # Input: s = "abciiidef", k = 3
    # Output: 3
    assert s.maxVowels("abciiidef", 3) == 3

    # Example 2:
    # Input: s = "aeiou", k = 2
    # Output: 2
    assert s.maxVowels("aeiou", 2) == 2

    # Example 3:
    # Input: s = "leetcode", k = 3
    # Output: 2
    assert s.maxVowels("leetcode", 3) == 2
