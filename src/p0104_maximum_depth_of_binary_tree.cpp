#include "tree.hpp"
#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <queue>

namespace P0104 {
    class Solution {
      public:
        int maxDepth(TreeNode *root) {
            if (root == nullptr) {
                return 0;
            }

            std::queue<TreeNode *> nodes_level_order;
            nodes_level_order.push(root);
            int depth = 0;

            while (!nodes_level_order.empty()) {
                const std::size_t level_size = nodes_level_order.size();
                for (std::size_t i = 0; i < level_size; ++i) {
                    TreeNode *node = nodes_level_order.front();
                    nodes_level_order.pop();
                    if (node->left != nullptr) {
                        nodes_level_order.push(node->left);
                    }
                    if (node->right != nullptr) {
                        nodes_level_order.push(node->right);
                    }
                }
                ++depth;
            }

            return depth;
        }

        int maxDepthRecursive(TreeNode *root) {
            if (root == nullptr) {
                return 0;
            }
            return std::max(maxDepthRecursive(root->left),
                            maxDepthRecursive(root->right)) +
                   1;
        }
    };

    TEST_CASE("0104 - Maximum Depth of Binary Tree",
              "[Tree][Depth-First Search][Breadth-First Search][Binary Tree]") {
        Solution s;
        SECTION("Example 1") {
            BinaryTree tree(3);
            tree << 9 << 20 << nullptr << nullptr << 15 << 7;
            REQUIRE(s.maxDepth(tree.get_root()) == 3);
            REQUIRE(s.maxDepthRecursive(tree.get_root()) == 3);
        }
        SECTION("Example 2") {
            BinaryTree tree(1);
            tree << nullptr << 2;
            REQUIRE(s.maxDepth(tree.get_root()) == 2);
            REQUIRE(s.maxDepthRecursive(tree.get_root()) == 2);
        }
    }
} // namespace P0104