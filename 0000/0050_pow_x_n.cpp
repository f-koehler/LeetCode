#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

class Solution {
  public:
    double myPow(double x, int n) {
        if (n == 0) {
            return 1.0;
        }
        if (n < 0) {
            const auto inverse = 1.0 / x;
            const auto half = myPow(inverse, -(n / 2));
            if (n % 2) {
                return half * half * inverse;
            }
            return half * half;
        }
        const auto half = myPow(x, n / 2);
        if (n % 2) {
            return half * half * x;
        }
        return half * half;
    }
};

TEST_CASE("0050 - Pow(x, n)", "[Math][Recursion]") {
    SECTION("Example 1") {
        Solution s;
        REQUIRE(s.myPow(2.00000, 10) == Catch::Approx(1024.00000));
    }
    SECTION("Example 2") {
        Solution s;
        REQUIRE(s.myPow(2.10000, 3) == Catch::Approx(9.26100));
    }
    SECTION("Example 3") {
        Solution s;
        REQUIRE(s.myPow(2.00000, -2) == Catch::Approx(0.25000));
    }
}