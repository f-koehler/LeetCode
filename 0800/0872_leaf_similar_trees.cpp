#include <catch2/catch_test_macros.hpp>
#include <deque>

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
        const TreeNode *tree1 = new TreeNode(
            3,
            new TreeNode(5, new TreeNode(6),
                         new TreeNode(2, new TreeNode(7), new TreeNode(4))),
            new TreeNode(1, new TreeNode(9), new TreeNode(8)));
        const TreeNode *tree2 = new TreeNode(
            3, new TreeNode(5, new TreeNode(6), new TreeNode(7)),
            new TreeNode(1, new TreeNode(4),
                         new TreeNode(2, new TreeNode(9), new TreeNode(8))));
        REQUIRE(s.leafSimilar(tree1, tree2));
    }
    SECTION("Exampel 2") {
        const TreeNode *tree1 =
            new TreeNode(1, new TreeNode(2), new TreeNode(3));
        const TreeNode *tree2 =
            new TreeNode(1, new TreeNode(3), new TreeNode(2));
        REQUIRE(!s.leafSimilar(tree1, tree2));
    }
}