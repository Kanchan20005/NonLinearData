#include "AVLTree.h"
#include <algorithm>
#include <iostream>
using namespace std;

AVLTree::~AVLTree() {
    deleteTree(root);
}

void AVLTree::deleteTree(Node* node) {
    // Recursively remove all nodes in the BST (used by the destructor). 
    // By doing this recursively, we start removing nodes from the bottom
    // of the tree (leaf nodes), which is most efficiently because it does
    // not require replacing any nodes.

    if (node == nullptr)
        return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}


//WithoutRebalancing, it's similar to the Binary search tree function
void AVLTree::insertWithoutRebalance(Node* node) {
    //When the tree is emply, the first item is inserted in the root node
    if (root == nullptr) {
        root = node;
        return;
    }

    Node* currNode = root;
    //When the the tree is not empty, it runs through the loop and inserts the key in correct node.
    while (currNode != nullptr) {
        //Checking if the newkwy is les than the current node
        if (node->key <= currNode->key) {
            //Checking if we reach at the leaf node or does not have any node in the left side.
            if (currNode->left == nullptr) {
                //inserting the node in the left side of the parent node if it is empty
                currNode->left = node;
                currNode->left->parent = currNode;
                currNode = currNode->left;
                return;
            }
            //If the node is node going to the left child node.
            else {
                currNode = currNode->left;
            }
        }
        //Checking if the key in the new node is greater than the current node
        else {
        //Checking if we reach at the last node or leaf node.
            if (currNode->right == nullptr) {
                //Inserting the node if we reach at the last node
                currNode->right = node;
                currNode->right->parent = currNode;
                currNode = currNode->right;
                return;
            }

            //Going to the right if we are not at the last node.
            else {
                currNode = currNode->right;
            }
        }
    }
}



void AVLTree::insert(Node* node) {

    //When the tree is emply, the first item is inserted in the root node
    if (root == nullptr) {
        root = node;
        return;
    }

    Node* currNode = root;
    //Looping until the correct position for the insertion is found
    while (currNode != nullptr) {
        //Going to the left if the node key to be inserted is less than the current node
        if (node->key <= currNode->key) {
            //inserting the node to the left if reached to the position to insert
            if (currNode->left == nullptr) {
                //inserting the node
                currNode->left = node;
                currNode->left->parent = currNode;
                currNode = currNode->left;
                //Storing the parent of the node to be inserted
                Node* LeftNodeParent = currNode->parent;
                // Rebalancing the tree after insertion
                while (LeftNodeParent != nullptr) {
                    rebalance(LeftNodeParent);
                    LeftNodeParent = LeftNodeParent->parent;
                }
                return;
            }
            //Going back to loop if the last node for that branch is not reached
            else {
                currNode = currNode->left;
            }
        }
        //Going to the right if the node key to be inserted is greater than the current node
        else {
            //Inserting the node to be inserted the right node of current node as it points to null
            if (currNode->right == nullptr) {
                //Inserting the node to the right
                currNode->right = node;
                currNode->right->parent = currNode;
                currNode = currNode->right;
                //Saving the parent node of the key we are inserting.
                Node* RightNodeParent = currNode->parent;
                // Rebalancing the tree after insertion
                while (RightNodeParent != nullptr) {
                    rebalance(RightNodeParent);
                    RightNodeParent = RightNodeParent->parent;
                }
                return;
            }
            //Going to the right node if it does not reach to the leaf node.
            else {
                currNode = currNode->right;
            }
        }
    }
}

int AVLTree::Height(Node* node) {
    int leftHeight = -1;
    int rightHeight = -1;

    //Calculating the height in the left branch
    if (node->left != nullptr) {
        leftHeight = Height(node->left);
    }
    //Calculating the height in the right branch
    if (node->right != nullptr) {
        rightHeight = Height(node->right);
    }
    //Checking if either height is greater.
    if (leftHeight > rightHeight) {
        node->height = leftHeight + 1;
    }
    else {
        node->height = rightHeight + 1;
    }
    int CompleteHeight =  node->height;
    return CompleteHeight;
}

//Calculating the height of the current node
void AVLTree::HeightForRebalance(Node* node) {
    //initializing the left and right height as -1
    int leftHeight = -1;
    int rightHeight = -1;

    //Calculating the height in the left branch
    if (node->left != nullptr) {
        leftHeight = node->left->height;
        
    }
    //Calculating the height in the right branch
    if (node->right != nullptr) {
        rightHeight = node->right->height;
    }

    //Checking if either height is greater.
    if (leftHeight > rightHeight) {
        node->height = leftHeight + 1;
    }
    else {
        node->height = rightHeight + 1;
    }
}

int AVLTree::getingBalanceFactor(Node* node) {
    //initializing the left and right height as -1
    int leftHeight = -1;
    int rightHeight = -1;

    //Calculating left and right height
    if (node->left != nullptr) {
        leftHeight = node->left->height;
    }
    if (node->right != nullptr) {
        rightHeight = node->right->height;
    }
    //Calculating the balance factor
    int balanceFactor = leftHeight - rightHeight;
    return balanceFactor;
}

//This is the method for rebalancing after ther insertion of the new node
void AVLTree::rebalance(Node* node) {
    //calculating the height of the parent node 
    HeightForRebalance(node);

    //Conditioning if the balance factor is -2 as it shoulb either be -1, 0, or 1
    if (getingBalanceFactor(node) == -2) {
        //Rotating the node to right
        if (getingBalanceFactor(node->right) == 1) {
            rotateRight(node->right);
        }

        // A left rotation will now make the subtree balanced.
        return rotateLeft(node);
    }
    //Conditioning if the balance factor is 2 as it shoulb either be -1, 0, or 1
    else if (getingBalanceFactor(node) == 2) {
        //Rotating toward left
        if (getingBalanceFactor(node->left) == -1) {
            rotateLeft(node->left);
        }

        // A right rotation will now make the subtree balanced.
        return rotateRight(node);
    }
    return;
}

//Method to rotate the node to the left
void AVLTree::rotateLeft(Node* node) {
    //saving the parent's node's right node's left node
    Node* rightLeftChild = node->right->left;
    //checking if the parent is null pointer
    if (node->parent != nullptr) {
        //sifting the parent's left node with right node
        if (node == node->parent->left) {
            node->parent->left = node->right;
        }
        //sifting the parent's right node with node's right node

        if (node == node->parent->right) {
            node->parent->right = node->right;
        }
    }
    //if the parent node is nullpointer i.e when inserting a node in empty AVLTree
    else { // node is root
        root = node->right;
        root->parent = nullptr;
    }

    //Fixing the rotation
    node->right->left = node;
    node->right = rightLeftChild;
    //Updating the final height to check for rebalancing
    HeightForRebalance(node);

}
//Method to rotate the node to the right
void AVLTree::rotateRight(Node* node) {
    //saving a node for future reference
    Node* leftRightChild = node->left->right;
    //checking if the parent is null pointer
    if (node->parent != nullptr) {
        //Rotating to the right
        if (node == node->parent->left) {
            node->parent->left = node->left;
        }
        if (node == node->parent->right) {
            node->parent->right = node->left;
        }

    }
    //if the tree is empty
    else {
        root = node->left;
        root->parent = nullptr;
    }
    node->left->right = node;
    node->left = leftRightChild;
    //Updating the height after right rotation for future check
    HeightForRebalance(node);
}




int main(){
    // Single rotate left
    AVLTree b;
    //for (int i = 0; i < 100000; i++) {
     //   Node* bRoot;
    //    double r;
    //    if (i == 0)
    //    {    
    //         bRoot = new Node((double)rand() / (RAND_MAX));
    //        b.insert(bRoot);
    //        
    //    }
     //   else {
     //       r = ((double)rand() / (RAND_MAX));
     //       b.insert(new Node(r));


    //    }

   // }
    Node* bRoot = new Node(2);
    b.insert(bRoot);
    b.insert(new Node(1));
    b.insert(new Node(3));
    b.insert(new Node(4));
    b.insert(new Node(5));
    cout << bRoot->key << endl;
    cout << bRoot->left->key << " " << bRoot->right->key<< endl;
    cout << bRoot->right->left->key << " " << bRoot -> right->right->key << endl;


    // Rotate left then right
    AVLTree c;
    Node* cRoot = new Node(4);
    c.insert(cRoot);
   c.insert(new Node(3));
    c.insert(new Node(5));
    c.insert(new Node(1));
    c.insert(new Node(2));
    //

    cout << cRoot->key << endl;
    cout << cRoot->left->key << " " << cRoot->right->key<< endl;
    cout << cRoot->left->left->key << " " << cRoot->left -> right->key << endl;
    cout << b.Height(b.root)<<  endl;


}