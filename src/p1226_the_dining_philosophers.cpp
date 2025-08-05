#include <array>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include <chrono>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

namespace P1226 {
    void doAction() {
        std::this_thread::sleep_for(std::chrono::microseconds(50));
    }
    class DiningPhilosophers {
      private:
        std::array<std::mutex, 5> m_fork_mutexes;

      public:
        DiningPhilosophers() {}

        void wantsToEat(int philosopher, std::function<void()> pickLeftFork,
                        std::function<void()> pickRightFork,
                        std::function<void()> eat,
                        std::function<void()> putLeftFork,
                        std::function<void()> putRightFork) {
            std::scoped_lock lock(m_fork_mutexes[philosopher],
                                  m_fork_mutexes[(philosopher + 1) % 5]);
            pickLeftFork();
            pickRightFork();
            eat();
            putLeftFork();
            putRightFork();
        }
    };

    TEST_CASE("1226 - The Dining Philosophers", "[Concurrency]") {
        const int n = GENERATE(Catch::Generators::range(1, 60, 5));
        INFO("n = " << n);

        DiningPhilosophers philosophers;
        auto thread_func = [&philosophers](int philosopher) {
            philosophers.wantsToEat(philosopher, doAction, doAction, doAction,
                                    doAction, doAction);
        };
        {
            std::vector<std::jthread> threads;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < 5; ++j) {
                    threads.emplace_back(thread_func, j);
                }
            }
        }
    }
} // namespace P1226
