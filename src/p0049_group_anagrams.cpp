#include <algorithm>
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <deque>
#include <map>
#include <unordered_map>
#include <vector>

namespace P0049 {
    class Solution {
      public:
        using Hash = std::array<uint16_t, 26>;

        [[nodiscard]]
        static constexpr Hash hash_word(const std::string &word) noexcept {
            Hash hash = {0};
            std::ranges::for_each(word, [&hash](auto c) { ++hash[c - 'a']; });
            return hash;
        }

        std::vector<std::vector<std::string>>
        groupAnagrams(const std::vector<std::string> &strs) {
            std::vector<std::vector<std::string>> result;
            std::map<Hash, std::size_t> hash_to_index;

            for (const auto &word : strs) {
                if (const auto [pos, inserted] =
                        hash_to_index.emplace(hash_word(word), result.size());
                    inserted) {
                    result.emplace_back(1, word);
                } else {
                    result[pos->second].push_back(word);
                }
            }

            return result;
        }

        std::vector<std::vector<std::string>>
        groupAnagramsSorting(const std::vector<std::string> &strs) {
            std::vector<std::vector<std::string>> result;
            std::unordered_map<std::string, std::size_t> hash_to_index;

            for (const auto &word : strs) {
                std::string hash = word;
                std::ranges::sort(hash);

                if (const auto [pos, inserted] =
                        hash_to_index.emplace(hash, result.size());
                    inserted) {
                    result.emplace_back(1, word);
                } else {
                    result[pos->second].push_back(word);
                }
            }

            return result;
        }
    };

    auto sort_result(std::vector<std::vector<std::string>> &result) {
        for (auto &group : result) {
            std::ranges::sort(group);
        }
        std::ranges::sort(result, [](const auto &a, const auto &b) {
            return a.front() < b.front();
        });
    }
    TEST_CASE("0049 - Group Anagrams",
              "[Array][Hash Table][String][Sorting][NeetCode150]") {
        Solution s;

        SECTION("Without Sorting") {
            SECTION("Example 1") {
                auto result =
                    s.groupAnagrams({"eat", "tea", "tan", "ate", "nat", "bat"});
                sort_result(result);
                REQUIRE(result.size() == 3);

                REQUIRE(result[0].size() == 3);
                REQUIRE(result[0] ==
                        std::vector<std::string>{"ate", "eat", "tea"});

                REQUIRE(result[1].size() == 1);
                REQUIRE(result[1] == std::vector<std::string>{"bat"});

                REQUIRE(result[2].size() == 2);
                REQUIRE(result[2] == std::vector<std::string>{"nat", "tan"});
            }

            SECTION("Example 2") {
                auto result = s.groupAnagrams({""});
                sort_result(result);
                REQUIRE(result.size() == 1);
                REQUIRE(result[0].size() == 1);
                REQUIRE(result[0] == std::vector<std::string>{""});
            }

            SECTION("Example 3") {
                auto result = s.groupAnagrams({"a"});
                sort_result(result);
                REQUIRE(result.size() == 1);
                REQUIRE(result[0].size() == 1);
                REQUIRE(result[0] == std::vector<std::string>{"a"});
            }
        }
        SECTION("With Sorting") {
            SECTION("Example 1") {
                auto result = s.groupAnagramsSorting(
                    {"eat", "tea", "tan", "ate", "nat", "bat"});
                sort_result(result);
                REQUIRE(result.size() == 3);

                REQUIRE(result[0].size() == 3);
                REQUIRE(result[0] ==
                        std::vector<std::string>{"ate", "eat", "tea"});

                REQUIRE(result[1].size() == 1);
                REQUIRE(result[1] == std::vector<std::string>{"bat"});

                REQUIRE(result[2].size() == 2);
                REQUIRE(result[2] == std::vector<std::string>{"nat", "tan"});
            }

            SECTION("Example 2") {
                auto result = s.groupAnagramsSorting({""});
                sort_result(result);
                REQUIRE(result.size() == 1);
                REQUIRE(result[0].size() == 1);
                REQUIRE(result[0] == std::vector<std::string>{""});
            }

            SECTION("Example 3") {
                auto result = s.groupAnagramsSorting({"a"});
                sort_result(result);
                REQUIRE(result.size() == 1);
                REQUIRE(result[0].size() == 1);
                REQUIRE(result[0] == std::vector<std::string>{"a"});
            }
        }
    }
} // namespace P0049