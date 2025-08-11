#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace P0981 {
    class TimeMap {
      public:
        struct Value {
            int timestamp;
            std::string value;
        };

      private:
        std::unordered_map<std::string, std::vector<Value>> m_entries;

      public:
        TimeMap() {}

        void set(const std::string &key, const std::string &value,
                 int timestamp) {
            m_entries[key].emplace_back(timestamp, value);
        }

        std::string get(const std::string &key, int timestamp) const {
            const auto pos = m_entries.find(key);
            if (pos == m_entries.cend()) {
                return "";
            }

            const auto bucket_pos = std::upper_bound(
                pos->second.cbegin(), pos->second.cend(),
                Value{.timestamp = timestamp, .value = std::string()},
                [](const Value &a, const Value &b) {
                    return a.timestamp < b.timestamp;
                });

            // if the iterator is at the beginning of the bucket, the timestamp
            // we are looking for is smaller than all the ones stored in the
            // bucket -> return the emtpy string
            //
            // if this is not the case, the element preceding the result
            // iterator is the one we are looking for. it has the largest
            // timestamp smaller or equal compared to the desired one
            return (bucket_pos == pos->second.cbegin())
                       ? ""
                       : std::prev(bucket_pos)->value;
        }
    };

    /**
     * Your TimeMap object will be instantiated and called as such:
     * TimeMap* obj = new TimeMap();
     * obj->set(key,value,timestamp);
     * string param_2 = obj->get(key,timestamp);
     */

    TEST_CASE("0981 - Time Based Key-Value Store",
              "[Hash Table][String][Binary Search][Design]") {
        TimeMap map;
        map.set("foo", "bar", 1);
        REQUIRE(map.get("foo", 1) == "bar");
        REQUIRE(map.get("foo", 3) == "bar");
        map.set("foo", "bar2", 4);
        REQUIRE(map.get("foo", 4) == "bar2");
        REQUIRE(map.get("foo", 5) == "bar2");
    }
} // namespace P0981
