pub struct Solution {}

impl Solution {
    pub fn occurrences_of_element(nums: Vec<i32>, queries: Vec<i32>, x: i32) -> Vec<i32> {
        let occurences = nums
            .iter()
            .enumerate()
            .filter(|(_, val)| **val == x)
            .map(|(i, _)| i)
            .collect::<Vec<_>>();

        let num_occurrences = occurences.len();

        queries
            .iter()
            .map(|query| (query - 1) as usize)
            .map(|query| {
                if query < num_occurrences {
                    occurences[query] as i32
                } else {
                    -1i32
                }
            })
            .collect::<Vec<_>>()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_two_sum() {
        assert_eq!(
            Solution::occurrences_of_element(vec![1, 3, 1, 7], vec![1, 3, 2, 4], 1),
            vec![0, -1, 2, -1]
        );
        assert_eq!(
            Solution::occurrences_of_element(vec![1, 2, 3], vec![10], 5),
            vec![-1]
        );
    }
}
