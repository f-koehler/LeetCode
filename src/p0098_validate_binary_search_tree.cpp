#include <catch2/catch_test_macros.hpp>
#include <optional>
#include <stack>
#include <tree.hpp>

namespace LeetCode::P0098 {
    class Solution {
      public:
        [[nodiscard]] static bool isValidBST(TreeNode *root){
            // we can reformulate this problem: if we do in-order traversal, we
            // should produce an increasing sequence of numbers
            //
            // in-order traversal: first descend all the way to the left. Then
            // move up to the root (until we can descend to the right)

            std::stack<TreeNode *> path;
            TreeNode *current = root;
            std::optional<int> previous_value;
            while ((current != nullptr) || (!path.empty())) {
                // descend to left-most node
                while (current != nullptr) {
                    path.emplace(current);
                    current = current->left;
                }

                // we cannot descend to the left further, current must be
                // nullptr
                current = path.top();
                path.pop();

                // current->val is the next in-order value, check if it violates BST propery
                if (previous_value && (previous_value >= current->val)) {
                    return false;
                }
                previous_value = current->val;

                // switch to right subtree
                current = current->right;
            }
            return true;
        }
    };

    TEST_CASE("0098 - Validate Binary Search Tree",
              "[Tree][Depth-First Search][Binary Search Tree][Binary Tree]") {

        SECTION("Example 1") {
            // Input: root = [2,1,3]
            // Output: true
            REQUIRE(Solution::isValidBST(
                new TreeNode(2, new TreeNode(1), new TreeNode(3))));
        }

        SECTION("Example 2") {
            // Input: root = [5,1,4,null,null,3,6]
            // Output: false
            REQUIRE(!Solution::isValidBST(new TreeNode(
                5, new TreeNode(1),
                new TreeNode(4, new TreeNode(3), new TreeNode(6)))));
        }
    }
} // namespace LeetCode::P0098
