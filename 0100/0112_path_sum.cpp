#include "tree.hpp"
#include <catch2/catch_test_macros.hpp>
#include <stack>
#include <utility>

namespace P0112 {
    class Solution {
      public:
        bool hasPathSum(TreeNode *root, int targetSum) {
            if (root == nullptr) {
                return false;
            }
            if ((root->left == nullptr) && (root->right == nullptr)) {
                return targetSum == root->val;
            }

            const int remainder = targetSum - root->val;
            if (hasPathSum(root->left, remainder)) {
                return true;
            }
            return hasPathSum(root->right, remainder);
        }

        bool hasPathSumIterative(TreeNode *root, int target_sum) {
            if (root == nullptr) {
                return false;
            }

            // first element: node, second element: path sum up to and including
            // node
            std::stack<std::pair<TreeNode *, int>> stack;
            stack.push(std::make_pair(root, root->val));

            while (!stack.empty()) {
                TreeNode *current = stack.top().first;
                const int current_sum = stack.top().second;
                stack.pop();

                if ((current->left == nullptr) && (current->right == nullptr) &&
                    (current_sum == target_sum)) {
                    return true;
                }

                if (current->left != nullptr) {
                    stack.push(std::make_pair(
                        current->left, current_sum + current->left->val));
                }
                if (current->right != nullptr) {
                    stack.push(std::make_pair(
                        current->right, current_sum + current->right->val));
                }
            }

            return false;
        }
    };

    TEST_CASE("0112 - Path Sum", "[Tree][Binary Tree][Breadth-First "
                                 "Search][Depth-First Search][Binary Tree]") {
        Solution s;
        SECTION("Example 1") {
            BinaryTree tree(5);
            tree << 4 << 8 << 11 << nullptr << 13 << 4 << 7 << 2 << nullptr
                 << nullptr << nullptr << 1;
            REQUIRE(s.hasPathSum(tree.get_root(), 22));
            REQUIRE(s.hasPathSumIterative(tree.get_root(), 22));
        }
        SECTION("Example 2") {
            BinaryTree tree(1);
            tree << 2 << 3;
            REQUIRE(!s.hasPathSum(tree.get_root(), 5));
            REQUIRE(!s.hasPathSumIterative(tree.get_root(), 5));
        }
        SECTION("Example 3") {
            REQUIRE(!s.hasPathSum(nullptr, 0));
            REQUIRE(!s.hasPathSumIterative(nullptr, 0));
        }
    }
} // namespace P0112
