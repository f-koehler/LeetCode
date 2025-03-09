pub struct Solution {}

fn is_vowel(c: char) -> bool {
    matches!(c, 'a' | 'e' | 'i' | 'o' | 'u')
}

impl Solution {
    pub fn max_vowels(s: String, k: i32) -> i32 {
        let mut num_vowels = s.chars().take(k as usize).filter(|&c| is_vowel(c)).count();
        let mut max_vowels = num_vowels;

        let chars: Vec<char> = s.chars().collect();
        for i in 0..s.len().saturating_sub(k as usize) {
            if is_vowel(chars[i]) {
                num_vowels -= 1;
            }
            if is_vowel(chars[i + k as usize]) {
                num_vowels += 1;
            }
            max_vowels = max_vowels.max(num_vowels);
        }

        max_vowels as i32
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_two_sum() {
        // Example 1:
        // Input: s = "abciiidef", k = 3
        // Output: 3
        assert_eq!(Solution::max_vowels("abciiidef".to_string(), 3), 3);

        // Example 2:
        // Input: s = "aeiou", k = 2
        // Output: 2
        assert_eq!(Solution::max_vowels("aeiou".to_string(), 2), 2);

        // Example 3:
        // Input: s = "leetcode", k = 3
        // Output: 2
        assert_eq!(Solution::max_vowels("leetcode".to_string(), 3), 2);
    }
}
