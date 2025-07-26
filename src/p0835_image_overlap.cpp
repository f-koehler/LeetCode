#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <unordered_map>
#include <vector>

namespace P0835 {
    struct Vector {
        int x;
        int y;

        constexpr inline bool operator==(const Vector &rhs) const noexcept {
            return (x == rhs.x) && (y == rhs.y);
        }
    };

    class VectorHash {
      private:
        int m_image_size;
        std::hash<int> m_hash;

      public:
        explicit VectorHash(int image_size)
            : m_image_size(image_size) {}

        constexpr inline auto operator()(const Vector &pos) const noexcept {
            // exploit the geometry of the problem to prevent hash collisions
            return m_hash(pos.x * (2 * m_image_size) + pos.y);
        }
    };

    class Solution {
      public:
        int largestOverlap(const std::vector<std::vector<int>> &a,
                           const std::vector<std::vector<int>> &b) {
            const std::size_t n = a.size();

            std::vector<Vector> a_1;
            std::vector<Vector> b_1;
            a_1.reserve(n * n);
            b_1.reserve(n * n);

            // compute the position of the ones in the a and b matrices
            for (std::size_t row = 0; row < n; ++row) {
                for (std::size_t col = 0; col < n; ++col) {
                    if (a[row][col] == 1) {
                        a_1.emplace_back(row, col);
                    }
                    if (b[row][col] == 1) {
                        b_1.emplace_back(row, col);
                    }
                }
            }

            // check what translation would be required for any pair of ones to
            // overlap
            std::size_t max_overlap = 0;
            std::unordered_map<Vector, std::size_t, VectorHash>
                overlaps_per_translation(n * n, VectorHash(n));

            for (const Vector &a_vec : a_1) {
                for (const Vector &b_vec : b_1) {
                    const Vector translation = {a_vec.x - b_vec.x,
                                                a_vec.y - b_vec.y};
                    auto pos = overlaps_per_translation.find(translation);
                    if (pos == overlaps_per_translation.end()) {
                        // insert new count
                        overlaps_per_translation.insert({translation, 1});
                        max_overlap = std::max(1ul, max_overlap);
                    } else {
                        // increment existing count
                        max_overlap = std::max(++(pos->second), max_overlap);
                    }
                }
            }
            return max_overlap;
        }
    };

    TEST_CASE("0835 - Image Overlap", "[Array][Matrix]") {

        SECTION("Example 1") {
            // Input: img1 = [[1,1,0],[0,1,0],[0,1,0]], img2 =
            // [[0,0,0],[0,1,1],[0,0,1]] Output: 3
            Solution s;
            REQUIRE(s.largestOverlap({{1, 1, 0}, {0, 1, 0}, {0, 1, 0}},
                                     {{0, 0, 0}, {0, 1, 1}, {0, 0, 1}}) == 3);
        }

        SECTION("Example 2") {
            // Input: img1 = [[1]], img2 = [[1]]
            // Output: 1
            Solution s;
            REQUIRE(s.largestOverlap({{1}}, {{1}}) == 1);
        }

        SECTION("Example 3") {
            // Input: img1 = [[0]], img2 = [[0]]
            // Output: 0
            Solution s;
            REQUIRE(s.largestOverlap({{0}}, {{0}}) == 0);
        }
    }
} // namespace P0835
