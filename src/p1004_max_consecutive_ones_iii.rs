pub struct Solution {}

impl Solution {
    pub fn longest_ones(nums: Vec<i32>, k: i32) -> i32 {
        let mut flips = k;
        let mut left = 0;
        let mut right = 0;
        let mut max_len = 0;
        let n = nums.len();
        while right < n {
            if nums[right] == 0 {
                flips -= 1;
            }

            while flips < 0 {
                if nums[left] == 0 {
                    flips += 1;
                }
                left += 1;
            }

            right += 1;

            max_len = std::cmp::max(max_len, right - left);
        }
        max_len as i32
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_two_sum() {
        // Example 1:
        // Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
        // Output: 6
        assert_eq!(
            Solution::longest_ones(vec![1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0], 2),
            6
        );

        // Example 2:
        // Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
        // Output: 10
        assert_eq!(
            Solution::longest_ones(
                vec![0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1],
                3
            ),
            10
        )
    }
}
