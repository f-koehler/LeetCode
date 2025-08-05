#include <atomic>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include <functional>
#include <semaphore>
#include <sstream>
#include <thread>

namespace P1116 {
    std::ostringstream strm;

    void printNumber(int number) { strm << number; }

    class ZeroEvenOdd {
      private:
        int m_n;
        std::binary_semaphore m_sem_zero;
        std::binary_semaphore m_sem_even;
        std::binary_semaphore m_sem_odd;

      public:
        explicit ZeroEvenOdd(int n)
            : m_n(n),
              m_sem_zero(1),
              m_sem_even(0),
              m_sem_odd(0) {}

        void zero(std::function<void(int)> printNumber) {
            for (int i = 0; i < m_n; ++i) {
                m_sem_zero.acquire();
                printNumber(0);
                if (i % 2) {
                    m_sem_even.release();
                } else {
                    m_sem_odd.release();
                }
            }
        }

        void even(std::function<void(int)> printNumber) {
            for (int i = 2; i <= m_n; i += 2) {
                m_sem_even.acquire();
                printNumber(i);
                m_sem_zero.release();
            }
        }

        void odd(std::function<void(int)> printNumber) {
            for (int i = 1; i <= m_n; i += 2) {
                m_sem_odd.acquire();
                printNumber(i);
                m_sem_zero.release();
            }
        }
    };

    TEST_CASE("1116 - Print Zero Even Odd", "[Concurrency]") {
        const int repetition = GENERATE(Catch::Generators::range(0, 128));
        INFO("repetition = " << repetition);

        SECTION("Example 1") {
            // Input: n = 2
            // Output: "0102"
            strm.str("");
            ZeroEvenOdd obj(2);
            {
                std::jthread t1([&obj]() { obj.zero(printNumber); });
                std::jthread t2([&obj]() { obj.even(printNumber); });
                std::jthread t3([&obj]() { obj.odd(printNumber); });
            }
            REQUIRE(strm.str() == "0102");
        }

        SECTION("Example 1 (Permutation 1)") {
            // Input: n = 2
            // Output: "0102"
            strm.str("");
            ZeroEvenOdd obj(2);
            {
                std::jthread t2([&obj]() { obj.even(printNumber); });
                std::jthread t1([&obj]() { obj.zero(printNumber); });
                std::jthread t3([&obj]() { obj.odd(printNumber); });
            }
            REQUIRE(strm.str() == "0102");
        }

        SECTION("Example 1 (Permutation 3)") {
            // Input: n = 2
            // Output: "0102"
            strm.str("");
            ZeroEvenOdd obj(2);
            {
                std::jthread t3([&obj]() { obj.odd(printNumber); });
                std::jthread t2([&obj]() { obj.even(printNumber); });
                std::jthread t1([&obj]() { obj.zero(printNumber); });
            }
            REQUIRE(strm.str() == "0102");
        }

        SECTION("Example 2") {
            // Input: n = 5
            // Output: "0102030405"
            strm.str("");
            ZeroEvenOdd obj(5);
            {
                std::jthread t1([&obj]() { obj.zero(printNumber); });
                std::jthread t2([&obj]() { obj.even(printNumber); });
                std::jthread t3([&obj]() { obj.odd(printNumber); });
            }
            REQUIRE(strm.str() == "0102030405");
        }

        SECTION("Example 2 (Permutation 1)") {
            // Input: n = 5
            // Output: "0102030405"
            strm.str("");
            ZeroEvenOdd obj(5);
            {
                std::jthread t2([&obj]() { obj.even(printNumber); });
                std::jthread t1([&obj]() { obj.zero(printNumber); });
                std::jthread t3([&obj]() { obj.odd(printNumber); });
            }
            REQUIRE(strm.str() == "0102030405");
        }

        SECTION("Example 2 (Permutation 3)") {
            // Input: n = 5
            // Output: "0102030405"
            strm.str("");
            ZeroEvenOdd obj(5);
            {
                std::jthread t3([&obj]() { obj.odd(printNumber); });
                std::jthread t2([&obj]() { obj.even(printNumber); });
                std::jthread t1([&obj]() { obj.zero(printNumber); });
            }
            REQUIRE(strm.str() == "0102030405");
        }
    }
} // namespace P1116
