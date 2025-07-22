pub struct Solution {}

impl Solution {
    pub fn length_of_longest_substring(s: String) -> i32 {
        if s.is_empty() {
            return 0i32;
        }

        let mut start = 0usize;
        let mut max_length = 1usize;
        let mut chars = std::collections::HashMap::<char, usize>::new();
        chars.insert(
            s.chars()
                .into_iter()
                .next()
                .expect("We already checked that the string should not be empty"),
            0,
        );

        for (i, c) in s.chars().into_iter().enumerate().skip(1) {
            if let Some(&duplicate_index) = chars.get(&c) {
                max_length = max_length.max(i - start);

                for c2 in s[start..=duplicate_index].chars() {
                    chars.remove(&c2);
                }

                start = duplicate_index + 1
            }
            chars.insert(c, i);
        }

        max_length.max(s.len() - start) as i32
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_two_sum() {
        // Example 1:
        // Input: s = "abcabcbb"
        // Output: 3
        assert_eq!(
            Solution::length_of_longest_substring("abcabcbb".to_string()),
            3
        );

        // Example 2:
        // Input: s = "bbbbb"
        // Output: 1
        assert_eq!(
            Solution::length_of_longest_substring("bbbbb".to_string()),
            1
        );

        // Example 3:
        // Input: s = "pwwkew"
        // Output: 3
        assert_eq!(
            Solution::length_of_longest_substring("pwwkew".to_string()),
            3
        );

        // Example 4:
        // Input: s = "au"
        // Output: 2
        assert_eq!(Solution::length_of_longest_substring("au".to_string()), 2);
    }
}
