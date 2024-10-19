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
    auto tree_3_1 = std::make_unique<TreeNode>(1);
    auto tree_3_2 = std::make_unique<TreeNode>(3);
    auto tree_2_1 =
        std::make_unique<TreeNode>(2, tree_3_1.get(), tree_3_2.get());
    auto tree_2_2 = std::make_unique<TreeNode>(7);
    auto tree = std::make_unique<TreeNode>(4, tree_2_1.get(), tree_2_2.get());

    SECTION("Example 1") {
        const TreeNode *const node1 = s.searchBST(tree.get(), 2);
        REQUIRE(node1 != nullptr);
        REQUIRE(node1->val == 2);
        REQUIRE(node1->left != nullptr);
        REQUIRE(node1->left->val == 1);
        REQUIRE(node1->right != nullptr);
        REQUIRE(node1->right->val == 3);

        const TreeNode *const node2 = s.searchBSTRecursive(tree.get(), 2);
        REQUIRE(node2 != nullptr);
        REQUIRE(node2->val == 2);
        REQUIRE(node2->left != nullptr);
        REQUIRE(node2->left->val == 1);
        REQUIRE(node2->right != nullptr);
        REQUIRE(node2->right->val == 3);
    }
    SECTION("Example 2") {
        const TreeNode *const node1 = s.searchBST(tree.get(), 5);
        REQUIRE(node1 == nullptr);

        const TreeNode *const node2 = s.searchBSTRecursive(tree.get(), 5);
        REQUIRE(node2 == nullptr);
    }
}
