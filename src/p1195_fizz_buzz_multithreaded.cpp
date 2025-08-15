#include <catch2/catch_test_macros.hpp>
#include <functional>
#include <semaphore>
#include <sstream>
#include <thread>

namespace P1195 {
    std::ostringstream strm;

    void printFizz() { strm << "fizz,"; }
    void printBuzz() { strm << "buzz,"; }
    void printFizzBuzz() { strm << "fizzbuzz,"; }
    void printNumber(int x) { strm << x << ','; }

    class FizzBuzz {
      private:
        const int m_n;

        std::binary_semaphore m_sem_fizz;
        std::binary_semaphore m_sem_buzz;
        std::binary_semaphore m_sem_fizz_buzz;
        std::binary_semaphore m_sem_number;

      public:
        explicit FizzBuzz(int n)
            : m_n(n),
              m_sem_fizz(0),
              m_sem_buzz(0),
              m_sem_fizz_buzz(0),
              m_sem_number(1) {}

        // printFizz() outputs "fizz".
        void fizz(std::function<void()> printFizz) {
            for (int i = 3; i <= m_n; i += 3) {
                if (i % 5 == 0) {
                    continue;
                }
                m_sem_fizz.acquire();
                printFizz();

                // go back to number function which coordinates
                m_sem_number.release();
            }
        }

        // printBuzz() outputs "buzz".
        void buzz(std::function<void()> printBuzz) {
            for (int i = 5; i <= m_n; i += 5) {
                if (i % 3 == 0) {
                    continue;
                }
                m_sem_buzz.acquire();
                printBuzz();

                // go back to number function which coordinates
                m_sem_number.release();
            }
        }

        // printFizzBuzz() outputs "fizzbuzz".
        void fizzbuzz(std::function<void()> printFizzBuzz) {
            for (int i = 15; i <= m_n; i += 15) {
                m_sem_fizz_buzz.acquire();
                printFizzBuzz();

                // go back to number function which coordinates
                m_sem_number.release();
            }
        }

        // printNumber(x) outputs "x", where x is an integer.
        void number(std::function<void(int)> printNumber) {
            for (int i = 1; i <= m_n; ++i) {
                m_sem_number.acquire();
                if (i % 15 == 0) {
                    m_sem_fizz_buzz.release();
                } else if (i % 3 == 0) {
                    m_sem_fizz.release();
                } else if (i % 5 == 0) {
                    m_sem_buzz.release();
                } else {
                    printNumber(i);
                    m_sem_number.release();
                }
            }
        }
    };

    TEST_CASE("1195 - Fizz Buzz Multithreaded", "[Concurrency]") {

        SECTION("Example 1") {
            // Input: n = 15
            // Output:
            // [1,2,"fizz",4,"buzz","fizz",7,8,"fizz","buzz",11,"fizz",13,14,"fizzbuzz"]
            FizzBuzz fb(15);
            strm.clear();
            {
                std::jthread t1([&fb]() { fb.fizz(printFizz); });
                std::jthread t2([&fb]() { fb.buzz(printBuzz); });
                std::jthread t3([&fb]() { fb.fizzbuzz(printFizzBuzz); });
                std::jthread t4([&fb]() { fb.number(printNumber); });
            }
            REQUIRE(
                strm.str() ==
                "1,2,fizz,4,buzz,fizz,7,8,fizz,buzz,11,fizz,13,14,fizzbuzz,");
        }

        SECTION("Example 2") {
            // Input: n = 5
            // Output: [1,2,"fizz",4,"buzz"]
            FizzBuzz fb(5);
            strm.str("");
            {
                std::jthread t1([&fb]() { fb.fizz(printFizz); });
                std::jthread t2([&fb]() { fb.buzz(printBuzz); });
                std::jthread t3([&fb]() { fb.fizzbuzz(printFizzBuzz); });
                std::jthread t4([&fb]() { fb.number(printNumber); });
            }
            REQUIRE(strm.str() == "1,2,fizz,4,buzz,");
        }
    }
} // namespace P1195
