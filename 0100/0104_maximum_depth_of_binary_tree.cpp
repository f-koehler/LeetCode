#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <queue>

class TreeNode {
  public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode()
        : val(0),
          left(nullptr),
          right(nullptr) {}
    explicit TreeNode(int x)
        : val(x),
          left(nullptr),
          right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x),
          left(left),
          right(right) {}
};

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
        auto *root =
            new TreeNode(3, new TreeNode(9, nullptr, nullptr),
                         new TreeNode(20, new TreeNode(15, nullptr, nullptr),
                                      new TreeNode(7, nullptr, nullptr)));
        REQUIRE(s.maxDepth(root) == 3);
        REQUIRE(s.maxDepthRecursive(root) == 3);
    }
    SECTION("Example 2") {
        auto *root =
            new TreeNode(1, nullptr, new TreeNode(2, nullptr, nullptr));
        REQUIRE(s.maxDepth(root) == 2);
        REQUIRE(s.maxDepthRecursive(root) == 2);
    }
}