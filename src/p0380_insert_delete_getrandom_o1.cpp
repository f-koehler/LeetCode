#include <catch2/catch_test_macros.hpp>
#include <random>
#include <unordered_map>
#include <vector>

namespace P0380 {
    static constexpr std::size_t AllocationSize = 300'000;

    class RandomizedSet {
      private:
        std::vector<int> m_values;
        std::unordered_map<int, std::size_t> m_value_index_map;

        // We could make this faster by using a cheap but bad PRNG (like rand())
        // as it is probably enough for LC's basic uniformity testing. I rather
        // use a better one.
        std::default_random_engine m_prng;

      public:
        RandomizedSet() {
            m_values.reserve(AllocationSize);
            m_value_index_map.reserve(AllocationSize);
        }

        bool insert(int val) {
            // nothing to do if element presetn
            if (m_value_index_map.contains(val)) {
                return false;
            }

            // insert new element in the back
            m_value_index_map.emplace(val, m_values.size());
            m_values.push_back(val);
            return true;
        }

        bool remove(int val) {
            // the question not strictly says that there is one element present
            // when this op is called (only for getRandom)
            if (m_values.empty()) {
                return false;
            }

            auto pos = m_value_index_map.find(val);
            if (pos == m_value_index_map.end()) {
                return false;
            }

            const std::size_t index = pos->second;

            // deleting from the an arbitrary position in the vector is O(n)
            //
            // therefore we move the element we want to delete to the back where
            // we can remove it efficiently
            //
            // we are guarantueed that there is at least one element in the set
            // when this method is called

            // the value at the end of the vector get the index of the element
            // we remove
            //
            // this works also if there is only one element
            m_value_index_map[m_values.back()] = index;
            m_value_index_map.erase(val);

            // actually move the back element
            m_values[index] = m_values.back();

            // remove the back element from the vector
            m_values.pop_back();

            return true;
        }

        int getRandom() {
            return m_values[std::uniform_int_distribution<std::size_t>(
                0, m_values.size() - 1)(m_prng)];
        }
    };

    /**
     * Your RandomizedSet object will be instantiated and called as such:
     * RandomizedSet* obj = new RandomizedSet();
     * bool param_1 = obj->insert(val);
     * bool param_2 = obj->remove(val);
     * int param_3 = obj->getRandom();
     */

    TEST_CASE("0380 - Insert Delete GetRandom O(1)",
              "[Array][Hash Table][Math][Design][Randomized]") {
        SECTION("Example 1") {
            RandomizedSet set;
            REQUIRE(set.insert(1));
            REQUIRE(!set.remove(2));
            REQUIRE(set.insert(2));

            const int r1 = set.getRandom();
            REQUIRE(((r1 == 1) || (r1 == 2)));

            REQUIRE(set.remove(1));
            REQUIRE(!set.insert(2));
            REQUIRE(set.getRandom() == 2);
        }
        SECTION("Example 1") {
            RandomizedSet set;
            REQUIRE(set.insert(0));
            REQUIRE(set.insert(1));
            REQUIRE(set.insert(2));

            for (int i = 0; i < 256; ++i) {
                const int r = set.getRandom();
                REQUIRE(((r == 0) || (r == 1) || (r == 2)));
            }
        }
    }
} // namespace P0380
