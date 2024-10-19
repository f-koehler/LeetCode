#include "tree.hpp"
#include <catch2/catch_test_macros.hpp>

class Solution {
  public:
    TreeNode *deleteNode(TreeNode *root, int key) {
        if (root == nullptr) {
            return nullptr;
        }

        if (key < root->val) {
            // key must be in left subtree, delete it there and set its root as
            // left child of current node
            root->left = deleteNode(root->left, key);
            return root;
        }
        if (key > root->val) {
            // key must be in right subtree, delete it there and set its root as
            // right child of current node
            root->right = deleteNode(root->right, key);
            return root;
        }

        // current node has the desired key

        if (root->left == nullptr) {
            // there is no left subtree -> return right subtree
            return root->right;
        }
        if (root->right == nullptr) {
            // there is no right subtree -> return left subtree
            return root->left;
        }

        // find the smallest node in the right subtree, remove it from there and
        // make it the new root with the original left subtree as the left
        // childe and the remaining right subtree as the right child

        // find the smallest value in the right subtree
        TreeNode *smallestNode = findSmallestNode(root->right);

        // remove the smallest node from the right subtree
        root->right = deleteNode(root->right, smallestNode->val);

        // set left/right subtree as left/right subtree of smallest node
        smallestNode->left = root->left;
        smallestNode->right = root->right;
        root = smallestNode;
        return root;
    }

    TreeNode *findSmallestNode(TreeNode *node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
};

TEST_CASE("0450 - Delete Node in a BST",
          "[Tree][Binary Search Tree][Binary Tree]") {
    Solution s;

    SECTION("Example 1") {
        BinaryTree tree(5);
        tree << 3 << 6 << 2 << 4 << nullptr << 7;
        s.deleteNode(tree.get_root(), 3);

        BinaryTree expected(5);
        expected << 4 << 6 << 2 << nullptr << nullptr << 7;

        REQUIRE(tree == expected);
    }
    SECTION("Example 2") {
        BinaryTree tree(5);
        tree << 3 << 6 << 2 << 4 << nullptr << 7;
        s.deleteNode(tree.get_root(), 0);

        BinaryTree expected(5);
        expected << 3 << 6 << 2 << 4 << nullptr << 7;
        REQUIRE(tree == expected);
    }
    SECTION("Example 3") {
        // cppcheck-suppress knownConditionTrueFalse
        REQUIRE(s.deleteNode(nullptr, 0) == nullptr);
    }
}
