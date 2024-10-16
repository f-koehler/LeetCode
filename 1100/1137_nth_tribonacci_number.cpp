#include <array>
#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <deque>

/*
 * There is also the idea of a constant time solution using a Binet-style
 * formula. Unfortunately, the relevant constants (eigenvalues of the matrix
 * {{1,1,1},{1,0,0},{0,1,0}} take an ugly form. There are some papers where
 * approximate values are given.
 */

class Solution {
  private:
    std::deque<uint64_t> m_tribonacci_numbers{0, 1, 1};

  public:
    int tribonacci(int n) {
        int max_n = static_cast<int>(m_tribonacci_numbers.size() - 1);
        while (max_n <= n) {
            m_tribonacci_numbers.push_back(m_tribonacci_numbers[max_n] +
                                           m_tribonacci_numbers[max_n - 1] +
                                           m_tribonacci_numbers[max_n - 2]);
            ++max_n;
        }

        // The problem statement guarantees us, that the solution fits into the
        // given integer type. I would have preferred it to be at least an
        // unsigned integer type.
        return static_cast<int>(m_tribonacci_numbers[n]);
    }

    int tribonacciNoCache(int n) {
        std::array<uint64_t, 3> buffer{0, 1,
                                       1}; // ring buffer-like array containg
                                           // the last three tribonacci numbers
        for (int i = 3; i <= n; ++i) {
            buffer[i % 3] = buffer[0] + buffer[1] + buffer[2];
        }

        // The problem statement guarantees us, that the solution fits into the
        // given integer type. I would have preferred it to be at least an
        // unsigned integer type.
        return static_cast<int>(buffer[n % 3]);
    }
};

TEST_CASE("1137 - N-th Tribonacci Number",
          "[Math][Dynamic Programming][Memoization]") {
    Solution s;
    SECTION("Example 1") {
        REQUIRE(s.tribonacci(4) == 4);
        REQUIRE(s.tribonacciNoCache(4) == 4);
    }
    SECTION("Example 2") {
        REQUIRE(s.tribonacci(25) == 1389537);
        REQUIRE(s.tribonacciNoCache(25) == 1389537);
    }
}
