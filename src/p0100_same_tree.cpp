#include "tree.hpp"
#include <catch2/catch_test_macros.hpp>
#include <stack>

namespace LeetCode::P0100 {
    class Solution {
      public:
        [[nodiscard]] static bool isSameTree(TreeNode *lhs, TreeNode *rhs) {
            if (lhs == nullptr) {
                if (rhs == nullptr) {
                    return true;
                }
                return false;
            } else if (rhs == nullptr) {
                return false;
            }

            std::stack<TreeNode *> to_visit_lhs;
            std::stack<TreeNode *> to_visit_rhs;
            to_visit_lhs.emplace(lhs);
            to_visit_rhs.emplace(rhs);

            while (!to_visit_lhs.empty() && !to_visit_rhs.empty()) {
                auto *current_lhs = to_visit_lhs.top();
                auto *current_rhs = to_visit_rhs.top();
                to_visit_lhs.pop();
                to_visit_rhs.pop();

                // check value in current node
                if (current_lhs->val != current_rhs->val) {
                    return false;
                }

                // check that both trees match in having a left child for the current node or not
                if ((current_lhs->left == nullptr) != (current_rhs->left == nullptr)) {
                    return false;
                }

                // scan left child next (DFS)
                if (current_lhs->left != nullptr) {
                    to_visit_lhs.emplace(current_lhs->left);
                    to_visit_rhs.emplace(current_rhs->left);
                }

                // check that both trees match in having a right child for the current node or not
                if ((current_lhs->right == nullptr) != (current_rhs->right == nullptr)) {
                    return false;
                }

                // scan right child afterwards (DFS)
                if (current_lhs->right != nullptr) {
                    to_visit_lhs.emplace(current_lhs->right);
                    to_visit_rhs.emplace(current_rhs->right);
                }
            }
            return to_visit_lhs.empty() && to_visit_rhs.empty();
        }
    };

    TEST_CASE("0100 - Same Tree",
              "[Tree][Depth-First Search][Breadth-First Search][Binary Tree]") {

        SECTION("Example 1") {
            // Input: p = [1,2,3], q = [1,2,3]
            // Output: true
            TreeNode *tree = new TreeNode(1, new TreeNode(2), new TreeNode(3));
            REQUIRE(Solution::isSameTree(tree, tree));
        }

        SECTION("Example 2") {
            // Input: p = [1,2], q = [1,null,2]
            // Output: false
            TreeNode *left = new TreeNode(1, new TreeNode(2), nullptr);
            TreeNode *right = new TreeNode(1, nullptr, new TreeNode(2));
            REQUIRE(!Solution::isSameTree(left, right));
        }

        SECTION("Example 3") {
            // Input: p = [1,2,1], q = [1,1,2]
            // Output: false
            TreeNode *left = new TreeNode(1, new TreeNode(2), new TreeNode(1));
            TreeNode *right = new TreeNode(1, new TreeNode(1), new TreeNode(2));
            REQUIRE(!Solution::isSameTree(left, right));
        }
    }
} // namespace LeetCode::P0100
