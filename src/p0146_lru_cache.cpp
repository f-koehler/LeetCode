#include <catch2/catch_test_macros.hpp>
#include <list>
#include <unordered_map>

namespace P0146 {
    struct Entry {
        int key;
        int value;
    };
    class LRUCache {
      private:
        void move_to_front(std::list<Entry>::iterator it) {
            if (it == m_entries.begin()) {
                return;
            }
            // splice does not invalidate references/iterators
            m_entries.splice(m_entries.begin(), m_entries, it);
        }

      public:
        explicit LRUCache(int capacity)
            : m_capacity(capacity) {}

        int get(int key) {
            auto pos = m_key_to_iterator.find(key);
            if (pos == m_key_to_iterator.end()) {
                return -1;
            }
            move_to_front(pos->second);
            return m_entries.front().value;
        }

        void put(int key, int value) {
            auto pos = m_key_to_iterator.find(key);
            if (pos != m_key_to_iterator.end()) {
                // update existing entry for key and move entry to front
                pos->second->value = value;
                move_to_front(pos->second);
                return;
            }
            if (m_entries.size() == static_cast<std::size_t>(m_capacity)) {
                // evict least recently used entry from cache
                m_key_to_iterator.erase(m_entries.back().key);
                m_entries.pop_back();
            }

            // insert new entry in the front
            m_entries.emplace_front(key, value);
            m_key_to_iterator.emplace(key, m_entries.begin());
        }

      private:
        int m_capacity;
        std::list<Entry> m_entries;
        std::unordered_map<int, std::list<Entry>::iterator> m_key_to_iterator;
    };

    /**
     * Your LRUCache object will be instantiated and called as such:
     * LRUCache* obj = new LRUCache(capacity);
     * int param_1 = obj->get(key);
     * obj->put(key,value);
     */

    TEST_CASE("0146 - LRU Cache",
              "[Hash Table][Linked List][Design][Doubly-Linked List]") {
        LRUCache cache(2);
        cache.put(1, 1);
        cache.put(2, 2);
        REQUIRE(cache.get(1) == 1);
        cache.put(3, 3);
        REQUIRE(cache.get(2) == -1);
        cache.put(4, 4);
        REQUIRE(cache.get(1) == -1);
        REQUIRE(cache.get(3) == 3);
        REQUIRE(cache.get(4) == 4);
    }
} // namespace P0146
