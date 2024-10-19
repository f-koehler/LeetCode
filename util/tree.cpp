#include "tree.hpp"
#include <catch2/catch_test_macros.hpp>
#include <queue>
#include <sstream>
#include <stack>
#include <stdexcept>

TreeNode::TreeNode()
    : val(0),
      left(nullptr),
      right(nullptr) {}
TreeNode::TreeNode(int x)
    : val(x),
      left(nullptr),
      right(nullptr) {}
TreeNode::TreeNode(int x, TreeNode *left, TreeNode *right)
    : val(x),
      left(left),
      right(right) {}

BinaryTree::BinaryTree(int root_val) {
    m_nodes.emplace_back(std::make_unique<TreeNode>(root_val));
}
BinaryTree BinaryTree::from_node(TreeNode *node) {
    if (node == nullptr) {
        throw std::invalid_argument("Cannot convert nullptr to BinaryTree");
    }

    BinaryTree tree(node->val);
    std::queue<TreeNode *> nodes;
    nodes.push(node->left);
    nodes.push(node->right);

    while (!nodes.empty()) {
        TreeNode *current = nodes.front();
        nodes.pop();

        if (current == nullptr) {
            tree << nullptr;
        } else {
            tree << current->val;
            nodes.push(current->left);
            nodes.push(current->right);
        }
    }
    return tree;
}
void BinaryTree::advance_parent() {
    if (m_is_next_child_left) {
        m_is_next_child_left = false;
        return;
    }
    m_is_next_child_left = true;
    ++m_next_parent;
    const std::size_t n = m_nodes.size();
    while (m_next_parent < n) {
        if (m_nodes[m_next_parent] != nullptr) {
            return;
        }
        ++m_next_parent;
    }
}

BinaryTree &BinaryTree::operator<<(int val) {
    m_nodes.emplace_back(std::make_unique<TreeNode>(val));
    if (m_is_next_child_left) {
        m_nodes[m_next_parent]->left = m_nodes.back().get();
    } else {
        m_nodes[m_next_parent]->right = m_nodes.back().get();
    }
    advance_parent();
    return *this;
}
BinaryTree &BinaryTree::operator<<(nullptr_t) {
    m_nodes.emplace_back(std::unique_ptr<TreeNode>{nullptr});
    if (m_is_next_child_left) {
        m_nodes[m_next_parent]->left = nullptr;
    } else {
        m_nodes[m_next_parent]->right = nullptr;
    }
    advance_parent();
    return *this;
}

TreeNode *BinaryTree::get_root() { return m_nodes.front().get(); }
const TreeNode *BinaryTree::get_root() const { return m_nodes.front().get(); }

bool BinaryTree::operator==(const BinaryTree &rhs) const {
    std::stack<const TreeNode *> lhs_stack;
    std::stack<const TreeNode *> rhs_stack;
    lhs_stack.push(get_root());
    rhs_stack.push(rhs.get_root());

    while (!lhs_stack.empty() && !rhs_stack.empty()) {
        const TreeNode *lhs_node = lhs_stack.top();
        const TreeNode *rhs_node = rhs_stack.top();
        lhs_stack.pop();
        rhs_stack.pop();
        if (lhs_node == nullptr) {
            if (rhs_node == nullptr) {
                continue;
            }
            return false;
        }
        if (lhs_node->val != rhs_node->val) {
            return false;
        }
        lhs_stack.push(lhs_node->left);
        lhs_stack.push(lhs_node->right);
        rhs_stack.push(rhs_node->left);
        rhs_stack.push(rhs_node->right);
    }

    while (!lhs_stack.empty()) {
        if (lhs_stack.top() != nullptr) {
            return false;
        }
        lhs_stack.pop();
    }

    while (!rhs_stack.empty()) {
        if (rhs_stack.top() != nullptr) {
            return false;
        }
        rhs_stack.pop();
    }
    return true;
}

bool BinaryTree::operator!=(const BinaryTree &rhs) const {
    return !(*this == rhs);
}

std::ostream &operator<<(std::ostream &strm, const BinaryTree &tree) {
    if (tree.m_nodes.empty()) {
        strm << "[]";
        return strm;
    }

    strm << '[';
    const std::size_t n = tree.m_nodes.size() - 1;
    const TreeNode *node;
    for (std::size_t i = 0; i < n; ++i) {
        node = tree.m_nodes.at(i).get();
        if (node == nullptr) {
            strm << "null,";
        } else {
            strm << node->val << ',';
        }
    }
    node = tree.m_nodes.back().get();
    if (node == nullptr) {
        strm << "null]";
    } else {
        strm << node->val << ']';
    }

    return strm;
}

TEST_CASE("Util - Construct Binary Tree", "[Util][Binary Tree]") {
    SECTION("450 - Example 1") {
        BinaryTree tree(5);
        tree << 3 << 6 << 2 << 4 << nullptr << 7;

        auto root = tree.get_root();
        REQUIRE(root != nullptr);
        REQUIRE(root->val == 5);
        REQUIRE(root->left != nullptr);
        REQUIRE(root->left->val == 3);
        REQUIRE(root->left->left != nullptr);
        REQUIRE(root->left->left->val == 2);
        REQUIRE(root->left->left->left == nullptr);
        REQUIRE(root->left->left->right == nullptr);
        REQUIRE(root->left->right != nullptr);
        REQUIRE(root->left->right->val == 4);
        REQUIRE(root->left->right->left == nullptr);
        REQUIRE(root->left->right->right == nullptr);
        REQUIRE(root->right != nullptr);
        REQUIRE(root->right->val == 6);
        REQUIRE(root->right->left == nullptr);
        REQUIRE(root->right->right != nullptr);
        REQUIRE(root->right->right->val == 7);
        REQUIRE(root->right->right->left == nullptr);
        REQUIRE(root->right->right->right == nullptr);
    }
    SECTION("1161 - Example 1") {
        BinaryTree tree(1);
        tree << 7 << 0 << 7 << -8;

        auto root = tree.get_root();
        REQUIRE(root != nullptr);
        REQUIRE(root->val == 1);
        REQUIRE(root->left != nullptr);
        REQUIRE(root->left->val == 7);
        REQUIRE(root->left->left != nullptr);
        REQUIRE(root->left->left->val == 7);
        REQUIRE(root->left->left->left == nullptr);
        REQUIRE(root->left->left->right == nullptr);
        REQUIRE(root->left->right != nullptr);
        REQUIRE(root->left->right->val == -8);
        REQUIRE(root->left->right->left == nullptr);
        REQUIRE(root->left->right->right == nullptr);
        REQUIRE(root->right != nullptr);
        REQUIRE(root->right->val == 0);
        REQUIRE(root->right->left == nullptr);
        REQUIRE(root->right->right == nullptr);
    }
}

TEST_CASE("Util - Print Binary Tree", "[Util][Binary Tree]") {
    SECTION("450 - Example 1") {
        BinaryTree tree(5);
        tree << 3 << 6 << 2 << 4 << nullptr << 7;
        std::ostringstream strm;
        strm << tree;
        REQUIRE(strm.str() == "[5,3,6,2,4,null,7]");
    }
    SECTION("1161 - Example 1") {
        BinaryTree tree(1);
        tree << 7 << 0 << 7 << -8;
        std::ostringstream strm;
        strm << tree;
        REQUIRE(strm.str() == "[1,7,0,7,-8]");
    }
}
