#include "tree.hpp"
#include <catch2/catch_test_macros.hpp>
#include <deque>

class Solution {
  public:
    bool leafSimilar(const TreeNode *root1, const TreeNode *root2) {
        std::deque<int> leaf_values_1;
        std::deque<int> leaf_values_2;
        getLeafValues(root1, leaf_values_1);
        getLeafValues(root2, leaf_values_2);
        return leaf_values_1 == leaf_values_2;
    }
    void getLeafValues(const TreeNode *root, std::deque<int> &leaf_values) {
        bool is_leaf = true;
        if (root->left != nullptr) {
            getLeafValues(root->left, leaf_values);
            is_leaf = false;
        }
        if (root->right != nullptr) {
            getLeafValues(root->right, leaf_values);
            is_leaf = false;
        }
        if (is_leaf) {
            leaf_values.push_back(root->val);
        }
    }
};

TEST_CASE("0872 - Leaf-Similar Trees",
          "[Tree][Depth-First Search][Binary Tree]") {
    Solution s;
    SECTION("Example 1") {
        BinaryTree tree1(3);
        tree1 << 5 << 1 << 6 << 2 << 9 << 8 << nullptr << nullptr << 7 << 4;

        BinaryTree tree2(3);
        tree2 << 5 << 1 << 6 << 7 << 4 << 2 << nullptr << nullptr << nullptr
              << nullptr << nullptr << nullptr << 9 << 8;

        REQUIRE(s.leafSimilar(tree1.get_root(), tree2.get_root()));
    }
    SECTION("Exampel 2") {
        BinaryTree tree1(1);
        tree1 << 2 << 3;

        BinaryTree tree2(1);
        tree2 << 3 << 2;
        REQUIRE(!s.leafSimilar(tree1.get_root(), tree2.get_root()));
    }
}
