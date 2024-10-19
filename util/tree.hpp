#ifndef LEET_CODE_UTIL_TREE_HPP
#define LEET_CODE_UTIL_TREE_HPP

#include <deque>
#include <memory>
#include <ostream>

struct TreeNode {

    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode();
    explicit TreeNode(int x);
    TreeNode(int x, TreeNode *left, TreeNode *right);
};

class BinaryTree {
  public:
    friend std::ostream &operator<<(std::ostream &strm, const BinaryTree &tree);

  private:
    std::deque<std::unique_ptr<TreeNode>> m_nodes;
    std::size_t m_next_parent = 0;
    bool m_is_next_child_left = true;

    void advance_parent();

  public:
    explicit BinaryTree(int root_val);
    static BinaryTree from_node(TreeNode *node);

    BinaryTree &operator<<(int val);
    BinaryTree &operator<<(nullptr_t);
    TreeNode *get_root();
    const TreeNode *get_root() const;

    bool operator==(const BinaryTree &rhs) const;
    bool operator!=(const BinaryTree &rhs) const;
};

std::ostream &operator<<(std::ostream &strm, const BinaryTree &tree);

#endif
