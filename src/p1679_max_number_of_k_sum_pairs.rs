pub struct Solution {}

impl Solution {
    pub fn max_operations(nums: Vec<i32>, k: i32) -> i32 {
        debug_assert!(!nums.is_empty());
        debug_assert!(k > 0);
        let mut counts = std::collections::HashMap::<i32, i32>::new();

        for x in nums {
            *counts.entry(x).or_insert(0) += 1;
        }

        let mut result = 0i32;
        for (&num, &count) in &counts {
            if let Some(&pair_freq) = counts.get(&(k - num)) {
                result += count.min(pair_freq);
            }
        }
        result / 2
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_two_sum() {
        // Example 1:
        // Input: nums = [1,2,3,4], k = 5
        // Output: 2
        assert_eq!(Solution::max_operations(vec![1, 2, 3, 4], 5), 2);

        // Example 2:
        // Input: nums = [3,1,3,4,3], k = 6
        // Output: 1
        assert_eq!(Solution::max_operations(vec![3, 1, 3, 4, 3], 6), 1);
    }
}
