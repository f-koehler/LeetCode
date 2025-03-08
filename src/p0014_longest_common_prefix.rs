pub struct Solution {}

impl Solution {
    pub fn longest_common_prefix(strs: Vec<String>) -> String {
        debug_assert!(!strs.is_empty());
        let num_strs = strs.len();
        if num_strs == 1 {
            return strs[0].clone();
        }

        let len = strs.iter().map(|s| s.len()).min().expect("empty strs");
        for i in 0..len {
            for j in 1..num_strs {
                if strs[j].as_bytes()[i] != strs[0].as_bytes()[i] {
                    return strs[0][..i].to_string();
                }
            }
        }

        strs[0][..len].to_string()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_two_sum() {
        // Example 1:
        // Input: strs = ["flower","flow","flight"]
        // Output: "fl"
        assert_eq!(
            Solution::longest_common_prefix(vec![
                "flower".to_string(),
                "flow".to_string(),
                "flight".to_string()
            ]),
            "fl".to_string()
        );

        // Example 2:
        // Input: strs = ["dog","racecar","car"]
        // Output: ""
        assert_eq!(
            Solution::longest_common_prefix(vec![
                "dog".to_string(),
                "racecar".to_string(),
                "car".to_string()
            ]),
            "".to_string()
        );
    }
}
