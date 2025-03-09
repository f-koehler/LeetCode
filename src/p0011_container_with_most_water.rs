pub struct Solution {}

impl Solution {
    pub fn max_area(height: Vec<i32>) -> i32 {
        debug_assert!(height.len() >= 2);
        debug_assert!(height.iter().all(|&x| x >= 0));
        let mut left = 0;
        let mut right = height.len() - 1;
        let mut water: i32 = 0;
        while left < right {
            water = std::cmp::max(
                water,
                (right - left) as i32 * std::cmp::min(height[left], height[right]),
            );
            if height[left] < height[right] {
                left += 1;
            } else {
                right -= 1;
            }
        }
        water
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_two_sum() {
        // Example 1:
        // Input: height = [1,8,6,2,5,4,8,3,7]
        // Output: 49
        assert_eq!(Solution::max_area(vec![1, 8, 6, 2, 5, 4, 8, 3, 7]), 49);

        // Example 2:
        // Input: height = [1,1]
        // Output: 1
        assert_eq!(Solution::max_area(vec![1, 1]), 1);

        // Example 3
        // Input: height = [8,7,2,1]
        // Output: 7
        assert_eq!(Solution::max_area(vec![8, 7, 2, 1]), 7);
    }
}
