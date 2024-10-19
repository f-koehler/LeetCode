#include "tree.hpp"
#include <catch2/catch_test_macros.hpp>
#include <memory>

class Solution {
  public:
    TreeNode *searchBST(TreeNode *root, int val) {
        auto node = root;
        while ((node != nullptr) && (node->val != val)) {
            if (val < node->val) {
                node = node->left;
                continue;
            }
            node = node->right;
        }
        return node;
    }
    TreeNode *searchBSTRecursive(TreeNode *root, int val) {
        if (root == nullptr) {
            return nullptr;
        }
        if (root->val == val) {
            return root;
        }
        if (val < root->val) {
            return searchBST(root->left, val);
        }
        return searchBST(root->right, val);
    }
};

TEST_CASE("0700 - Search in a Binary Search Tree",
          "[Tree][Binary Search Tree][Binary Tree]") {
    Solution s;
    BinaryTree tree(4);
    tree << 2 << 7 << 1 << 3;

    SECTION("Example 1") {
        BinaryTree expected(2);
        expected << 1 << 3;

        auto *node1 = s.searchBST(tree.get_root(), 2);
        REQUIRE(node1 != nullptr);
        REQUIRE(BinaryTree::from_node(node1) == expected);

        auto *node2 = s.searchBSTRecursive(tree.get_root(), 2);
        REQUIRE(node2 != nullptr);
        REQUIRE(BinaryTree::from_node(node2) == expected);
    }
    SECTION("Example 2") {
        const TreeNode *const node1 = s.searchBST(tree.get_root(), 5);
        REQUIRE(node1 == nullptr);

        const TreeNode *const node2 = s.searchBSTRecursive(tree.get_root(), 5);
        REQUIRE(node2 == nullptr);
    }
}
