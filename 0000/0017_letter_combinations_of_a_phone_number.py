LETTERS_FOR_NUMBER = ["","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"]

class Solution:
    def build_all_combinations(self, digits: list[int], current: str, combinations: list[str]):
        len_digits = len(digits)
        len_current = len(current)
        if len_current >= len_digits:
            combinations.append(current)
            return

        letters = LETTERS_FOR_NUMBER[digits[len_current]]
        for letter in letters:
            self.build_all_combinations(digits, current + letter, combinations)

    def letterCombinations(self, digits: str) -> list[str]:
        if not digits:
            return []

        digits_int = [ord(d) - ord("0") for d in digits]
        combinations: list[str] = []
        self.build_all_combinations(digits_int, "", combinations)
        return combinations


def test_0017_letter_combinations_of_a_phone_number():
    s = Solution()

    example1 = s.letterCombinations("23")
    example1.sort()
    assert example1 == ["ad","ae","af","bd","be","bf","cd","ce","cf"]

    assert s.letterCombinations("") == []

    example3 = s.letterCombinations("2")
    assert example3 == ["a", "b", "c"]
