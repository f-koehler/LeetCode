pub struct Solution {}

impl Solution {
    pub fn max_profit(prices: Vec<i32>) -> i32 {
        let mut min_price = prices.first().expect("Prices should not be empty");
        let mut max_profit = 0i32;
        for price in prices.iter() {
            max_profit = max_profit.max(price - min_price);
            min_price = min_price.min(&price);
        }
        max_profit
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_two_sum() {
        // Example 1:
        // Input: prices = [7,1,5,3,6,4]
        // Output: 5
        assert_eq!(Solution::max_profit(vec![7, 1, 5, 3, 6, 4]), 5);

        // Example 2:
        // Input: prices = [7,6,4,3,1]
        // Output: 0
        assert_eq!(Solution::max_profit(vec![7, 6, 4, 3, 1]), 0);
    }
}
