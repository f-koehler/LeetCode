#include <catch2/catch_test_macros.hpp>
#include <memory>

struct TreeNode {
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
        auto node_3_1 = std::make_unique<TreeNode>(2),
             node_3_2 = std::make_unique<TreeNode>(4),
             node_3_4 = std::make_unique<TreeNode>(7),
             node_2_1 =
                 std::make_unique<TreeNode>(3, node_3_1.get(), node_3_2.get()),
             node_2_2 = std::make_unique<TreeNode>(6, nullptr, node_3_4.get()),
             tree =
                 std::make_unique<TreeNode>(5, node_2_1.get(), node_2_2.get());
        s.deleteNode(tree.get(), 3);
        REQUIRE(tree->val == 5);
        REQUIRE(tree->left != nullptr);
        REQUIRE(tree->right != nullptr);
        REQUIRE(tree->left->val == 4);
        REQUIRE(tree->left->left != nullptr);
        REQUIRE(tree->left->left->val == 2);
        REQUIRE(tree->left->right == nullptr);
        REQUIRE(tree->right != nullptr);
        REQUIRE(tree->right->val == 6);
        REQUIRE(tree->right->left == nullptr);
        REQUIRE(tree->right->right != nullptr);
        REQUIRE(tree->right->right->val == 7);
    }
    SECTION("Example 2") {
        auto node_3_1 = std::make_unique<TreeNode>(2),
             node_3_2 = std::make_unique<TreeNode>(4),
             node_3_4 = std::make_unique<TreeNode>(7),
             node_2_1 =
                 std::make_unique<TreeNode>(3, node_3_1.get(), node_3_2.get()),
             node_2_2 = std::make_unique<TreeNode>(6, nullptr, node_3_4.get()),
             tree =
                 std::make_unique<TreeNode>(5, node_2_1.get(), node_2_2.get());
        s.deleteNode(tree.get(), 0);
        REQUIRE(tree->val == 5);
        REQUIRE(tree->left != nullptr);
        REQUIRE(tree->right != nullptr);
        REQUIRE(tree->left->val == 3);
        REQUIRE(tree->left->left != nullptr);
        REQUIRE(tree->left->left->val == 2);
        REQUIRE(tree->left->right != nullptr);
        REQUIRE(tree->left->right->val == 4);
        REQUIRE(tree->right != nullptr);
        REQUIRE(tree->right->val == 6);
        REQUIRE(tree->right->left == nullptr);
        REQUIRE(tree->right->right != nullptr);
        REQUIRE(tree->right->right->val == 7);
    }
    SECTION("Example 3") {
        // cppcheck-suppress knownConditionTrueFalse
        REQUIRE(s.deleteNode(nullptr, 0) == nullptr);
    }
}
