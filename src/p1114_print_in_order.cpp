#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <sstream>
#include <thread>

namespace P1114 {
    std::ostringstream strm;
    void printFirst() { strm << "first"; }
    void printSecond() { strm << "second"; }
    void printThird() { strm << "third"; }

    class Foo {
      private:
        std::mutex m_mutex;
        std::condition_variable m_cv;
        std::size_t m_counter;

      public:
        Foo()
            : m_counter{1} {}

        void first(std::function<void()> printFirst) {
            // printFirst() outputs "first". Do not change or remove this line.
            printFirst();

            m_counter = 2;
            m_cv.notify_all();
        }

        void second(std::function<void()> printSecond) {
            // lock the mutex to access the CV, wait() will release the lock and
            // wait until the condition is fulfilled
            std::unique_lock<std::mutex> lock(m_mutex);
            m_cv.wait(lock, [this]() { return m_counter == 2; });

            // printSecond() outputs "second". Do not change or remove this
            // line.
            printSecond();

            m_counter = 3;
            m_cv.notify_all();
        }

        void third(std::function<void()> printThird) {
            // lock the mutex to access the CV, wait() will release the lock and
            // wait until the condition is fulfilled
            std::unique_lock<std::mutex> lock(m_mutex);
            m_cv.wait(lock, [this]() { return m_counter == 3; });

            // printThird() outputs "third". Do not change or remove this line.
            printThird();
        }
    };

    TEST_CASE("1114 - Print in Order", "[Concurrency]") {
        const int repetition = GENERATE(Catch::Generators::range(0, 128));
        INFO("repetition = " << repetition);
        SECTION("Example 1") {
            // Input: nums = [1,2,3]
            // Output: "firstsecondthird"
            strm.str("");
            Foo foo;
            {
                std::jthread t1([&foo]() { foo.first(printFirst); });
                std::jthread t2([&foo]() { foo.second(printSecond); });
                std::jthread t3([&foo]() { foo.third(printThird); });
            }
            REQUIRE(strm.str() == "firstsecondthird");
        }

        SECTION("Example 2") {
            // Input: nums = [1,3,2]
            // Output: "firstsecondthird"
            strm.str("");
            Foo foo;
            {
                std::jthread t1([&foo]() { foo.first(printFirst); });
                std::jthread t3([&foo]() { foo.third(printThird); });
                std::jthread t2([&foo]() { foo.second(printSecond); });
            }
            REQUIRE(strm.str() == "firstsecondthird");
        }
    }
} // namespace P1114
