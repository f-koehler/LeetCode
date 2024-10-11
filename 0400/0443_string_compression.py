class Solution:
    # Pretty much the same as the C++ solution
    def compress(self, chars: list[str]) -> int:
        dest = 0
        curr = 0
        length = len(chars)

        while curr < length:
            c = chars[curr]
            group_length = 0

            while (curr < length) and (chars[curr] == c):
                curr += 1
                group_length += 1

            dest += 1

            if group_length > 1:
                for digit in str(group_length):
                    chars[dest] = digit
                    dest += 1
        del chars[dest:]
        return dest


def test_0443_string_compression():
    s = Solution()
    chars = ["a", "a", "b", "b", "c", "c", "c"]
    assert s.compress(chars) == 6
    assert chars == ["a", "2", "b", "2", "c", "3"]

    chars = ["a"]
    assert s.compress(chars) == 1
    assert chars == ["a"]

    chars = ["a", "b", "b", "b", "b", "b", "b", "b", "b", "b", "b", "b", "b"]
    assert s.compress(chars) == 4
    assert chars == ["a", "b", "1", "2"]
