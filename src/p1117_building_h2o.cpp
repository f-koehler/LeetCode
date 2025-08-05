#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include <functional>
#include <semaphore>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

namespace P1117 {
    std::ostringstream strm;

    void releaseHydrogen() { strm << 'H'; }
    void releaseOxygen() { strm << 'O'; }

    class H2O {
      private:
        int num_hydrogen;
        std::binary_semaphore m_sem_hydrogen;
        std::binary_semaphore m_sem_oxygen;

      public:
        H2O()
            : num_hydrogen(0),
              m_sem_hydrogen(1),
              m_sem_oxygen(0) {}

        void hydrogen(std::function<void()> releaseHydrogen) {
            m_sem_hydrogen.acquire();
            // releaseHydrogen() outputs "H". Do not change or remove this line.
            releaseHydrogen();
            ++num_hydrogen;
            if (num_hydrogen % 2 == 0) {
                m_sem_oxygen.release();
            } else {
                m_sem_hydrogen.release();
            }
        }

        void oxygen(std::function<void()> releaseOxygen) {
            m_sem_oxygen.acquire();

            // releaseOxygen() outputs "O". Do not change or remove this line.
            releaseOxygen();
            m_sem_hydrogen.release();
        }
    };

    TEST_CASE("1117 - Building H2O", "[Concurrency]") {
        const int repetition = GENERATE(Catch::Generators::range(0, 128));
        INFO("repetition = " << repetition);

        SECTION("Example 1") {
            // Input: water = "HOH"
            // Output: "HHO"
            const std::string water("HOH");
            const int length = water.length();

            strm.str("");
            H2O h2o;

            {
                std::vector<std::jthread> threads;
                threads.reserve(water.length());
                auto func_oxygen = [&h2o]() { h2o.oxygen(releaseOxygen); };
                auto func_hydrogen = [&h2o]() {
                    h2o.hydrogen(releaseHydrogen);
                };
                for (char c : water) {
                    if (c == 'O') {
                        threads.emplace_back(func_oxygen);
                    } else {
                        threads.emplace_back(func_hydrogen);
                    }
                }
            }
            const std::string output = strm.str();

            INFO("output = " << output);
            for (int i = 0; i < length; i += 3) {
                INFO("triplet " << i << " = " << output.substr(i, 3));
                int num_h = 0;
                int num_o = 0;
                for (int j = i; j < i + 3; ++j) {
                    if (output[j] == 'H') {
                        ++num_h;
                    } else if (output[j] == 'O') {
                        ++num_o;
                    }
                }
                REQUIRE(num_h == 2);
                REQUIRE(num_o == 1);
            }
        }

        SECTION("Example 2") {
            // Input: water = "OOHHHH"
            // Output: "HHOHHO"
            const std::string water("OOHHHH");
            const int length = water.length();

            strm.str("");
            H2O h2o;

            {
                std::vector<std::jthread> threads;
                threads.reserve(water.length());
                auto func_oxygen = [&h2o]() { h2o.oxygen(releaseOxygen); };
                auto func_hydrogen = [&h2o]() {
                    h2o.hydrogen(releaseHydrogen);
                };
                for (char c : water) {
                    if (c == 'O') {
                        threads.emplace_back(func_oxygen);
                    } else {
                        threads.emplace_back(func_hydrogen);
                    }
                }
            }
            const std::string output = strm.str();

            INFO("output = " << output);
            for (int i = 0; i < length; i += 3) {
                INFO("triplet " << i << " = " << output.substr(i, 3));
                int num_h = 0;
                int num_o = 0;
                for (int j = i; j < i + 3; ++j) {
                    if (output[j] == 'H') {
                        ++num_h;
                    } else if (output[j] == 'O') {
                        ++num_o;
                    }
                }
                REQUIRE(num_h == 2);
                REQUIRE(num_o == 1);
            }
        }
    }
} // namespace P1117
