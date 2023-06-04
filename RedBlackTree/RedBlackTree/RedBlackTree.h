#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

// A node in the red-black tree that stores a double
class RBTNode {
public:
    double key;
    // Whether the node is red (false denotes black)
    bool red = true;
    int height = 0;

    RBTNode* left = nullptr;
    RBTNode* right = nullptr;
    RBTNode* parent = nullptr;

    RBTNode(double nodeKey) {
        key = nodeKey;
    }
};

// A red-black tree that can only insert
class RedBlackTree
{
public:
    RedBlackTree() {};
    ~RedBlackTree();

    // Insert a new element and rebalance the tree
    void insert(RBTNode* node);
    // Added function for height and root node.
    int Height(RBTNode* node);
    int Height();


private:
    RBTNode* root = nullptr;
    void deleteTree(RBTNode* node);

    //Added Helper function for the insert function for RedBlackTree
    void validation(RBTNode* node);
    void RotateLeft(RBTNode* node);
    void RotateRight(RBTNode* node);
};

#endif // !REDBLACKTREE_H