#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include <functional>
#include <semaphore>
#include <sstream>
#include <thread>

namespace P1115 {
    std::ostringstream strm;
    void printFoo() { strm << "foo"; }
    void printBar() { strm << "bar"; }

    class FooBar {
      private:
        int m_n;
        std::binary_semaphore m_sem_foo;
        std::binary_semaphore m_sem_bar;

      public:
        explicit FooBar(int n)
            : m_n(n),
              m_sem_foo(1),
              m_sem_bar(0) {}

        void foo(std::function<void()> printFoo) {

            for (int i = 0; i < m_n; i++) {
                m_sem_foo.acquire();
                // printFoo() outputs "foo". Do not change or remove this line.
                printFoo();
                m_sem_bar.release();
            }
        }

        void bar(std::function<void()> printBar) {

            for (int i = 0; i < m_n; i++) {
                m_sem_bar.acquire();
                // printBar() outputs "bar". Do not change or remove this line.
                printBar();
                m_sem_foo.release();
            }
        }
    };

    TEST_CASE("1115 - Print FooBar Alternately", "[Concurrency]") {
        const int repetition = GENERATE(Catch::Generators::range(0, 128));
        INFO("repetition = " << repetition);

        SECTION("Example 1") {
            // Input: n = 1
            // Output: "foobar"
            strm.str("");
            FooBar foo_bar(1);
            {
                std::jthread t1([&foo_bar]() { foo_bar.foo(printFoo); });
                std::jthread t2([&foo_bar]() { foo_bar.bar(printBar); });
            }
            REQUIRE(strm.str() == "foobar");
        }

        SECTION("Example 1 (flipped)") {
            // Input: n = 1
            // Output: "foobar"
            strm.str("");
            FooBar foo_bar(1);
            {
                std::jthread t2([&foo_bar]() { foo_bar.bar(printBar); });
                std::jthread t1([&foo_bar]() { foo_bar.foo(printFoo); });
            }
            REQUIRE(strm.str() == "foobar");
        }

        SECTION("Example 2") {
            // Input: n = 2
            // Output: "foobarfoobar"
            strm.str("");
            FooBar foo_bar(2);
            {
                std::jthread t1([&foo_bar]() { foo_bar.foo(printFoo); });
                std::jthread t2([&foo_bar]() { foo_bar.bar(printBar); });
            }
            REQUIRE(strm.str() == "foobarfoobar");
        }

        SECTION("Example 2 (flipped)") {
            // Input: n = 2
            // Output: "foobarfoobar"
            strm.str("");
            FooBar foo_bar(2);
            {
                std::jthread t2([&foo_bar]() { foo_bar.bar(printBar); });
                std::jthread t1([&foo_bar]() { foo_bar.foo(printFoo); });
            }
            REQUIRE(strm.str() == "foobarfoobar");
        }
    }
} // namespace P1115
