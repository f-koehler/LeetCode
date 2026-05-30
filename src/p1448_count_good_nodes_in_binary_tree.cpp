#include "tree.hpp"
#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <stack>

namespace LeetCode::P1448 {
    class Solution {
      public:
        [[nodiscard]] static int goodNodes(TreeNode *root) pre(root != nullptr)
            post(result : result >= 1) {
            using PathEntry = std::tuple<TreeNode *, int>;
            int num_good_nodes = 0;

            std::stack<PathEntry> path;
            path.emplace(root, root->val);

            while (!path.empty()) {
                auto [current, path_max] = path.top();
                path.pop();
                contract_assert((current->val >= -10000) &&
                                (current->val <= 10000));

                if(current->val >= path_max) {
                    ++num_good_nodes;
                    path_max = current->val;
                }

                if(current->left != nullptr) {
                    path.emplace(current->left, path_max);
                }
                if(current->right != nullptr) {
                    path.emplace(current->right, path_max);
                }
            }

            return num_good_nodes;
        }
    };

    TEST_CASE("1448 - Count Good Nodes in Binary Tree",
              "[Tree][Depth-First Search][Breadth-First Search][Binary Tree]") {

        SECTION("Example 1") {
            // Input: root = [3,1,4,3,null,1,5]
            // Output: 4
            TreeNode *root =
                new TreeNode(3, new TreeNode(1, new TreeNode(3), nullptr),
                             new TreeNode(4, new TreeNode(1), new TreeNode(5)));
            REQUIRE(Solution::goodNodes(root) == 4);
        }

        SECTION("Example 2") {
            // Input: root = [3,3,null,4,2]
            // Output: 3
            TreeNode *root = new TreeNode(
                3, new TreeNode(3, new TreeNode(4), new TreeNode(2)), nullptr);
            REQUIRE(Solution::goodNodes(root) == 3);
        }

        SECTION("Example 3") {
            // Input: root = [1]
            // Output: 1
            TreeNode *root = new TreeNode(1);
            REQUIRE(Solution::goodNodes(root) == 1);
        }
    }
} // namespace LeetCode::P1448
