#include "IndexedBST.h"
#include <iostream>


//Name: Kanchan Bhattarai
//Non-linear Programming
//Assignment 6

Node* IndexedBST::search(double desiredKey) {
    Node* cur = root;
    //Searching the desiredKey in the BST through while loop
    while (cur != nullptr) {
        // Checking if the current key value matches the desiredKey value
        if (cur->key == desiredKey) {
            return cur;
        }

        //Going to right if the key is not found
        else if (desiredKey > cur->key) {

            cur = cur->left;
        }

        //Going to left if the key is not found
        else{
            cur = cur->right;
        }
    }
    //Returning null if nothing is found
    return nullptr;
}

Node* IndexedBST::at(int index) {
    Node* cur = root;
    while (cur != nullptr) {
        if (index == cur->leftSize)
            return cur;     // Found
        else if (index < cur->leftSize)
            cur = cur->left;    // index is in left subtree
        else {
            // index is in right subtree
            index = index - cur->leftSize - 1;
            cur = cur->right;
        }
    }

    return nullptr;
}

void IndexedBST::insert(Node* node) {

    //Inserting the first node.
    if (root == nullptr) {
        root = node;
        return;
    }

    Node* currentNode = root;
    while (currentNode != nullptr) {
        //Going to the left node if the node to be inserted is less than the current node
        if (node->key <= currentNode->key) {
            //Creating a node if the node is leaf node.
            if (currentNode->left == nullptr) {
                currentNode->left = node;
                currentNode->left->parent = currentNode;
                currentNode = currentNode->left;

                //Updating the size after adding a left node
                while (currentNode != root) {
                    if (currentNode == currentNode->parent->left)
                        currentNode->parent->leftSize += 1;
                    currentNode = currentNode->parent;
                }
                return;
            }
            //Go to left to find the nullptr to insert the new node
            else {
                currentNode = currentNode->left;
            }
        }
        //Going to the right node if the node to be inserted is more than the current node
        else {
            //Creating a node if the node is leaf node.
            if (currentNode->right == nullptr) {
                currentNode->right = node;
                currentNode->right->parent = currentNode;
                currentNode = currentNode->right;

                //Updating the size after adding a left node
                while (currentNode != root) {
                    if (currentNode == currentNode->parent->left)
                        currentNode->parent->leftSize += 1;
                    currentNode = currentNode->parent;
                }

                return;
            }
            //Go to right to find the nullptr to insert the new node
            else {
                currentNode = currentNode->right;
            }
        }
    }
}

bool IndexedBST::remove(double key) {
    Node* currentNode = root;

    //Returning False if the the root is NullPtr
    if (currentNode == nullptr) {
        return false;
    }

    //Returning False if the the root is NullPtr
    bool rootRemoved = false;
    if (key == currentNode->key) {
        rootRemoved = true;
    }

    while (currentNode != nullptr) {
        //Looping until the currentNodeKey matches with the Key to be removed
        if (key == currentNode->key) {
            Node* SizeUpdate = currentNode;
            //Checking if the node is leaf node
            if (currentNode->left == nullptr && currentNode->right == nullptr) {

                //If we have removed the root node returning true and ending the loop
                if (rootRemoved) {
                    root = nullptr;
                    return true;
                }
                //if the left node is currentNode then removing the left node
                if (currentNode->parent->left == currentNode) {
                    //looping to update the size
                    while (SizeUpdate != root) {
                        if (SizeUpdate->parent->left == SizeUpdate) {
                            if (SizeUpdate->parent->leftSize > 0)
                                SizeUpdate->parent->leftSize -= 1;
                        }
                        SizeUpdate = SizeUpdate->parent;
                    }
                    currentNode->parent->left = nullptr;
                    currentNode = nullptr;
                    return true;
                }
                //if the right node is currentNode then removing the right node
                else if (currentNode->parent->right == currentNode) {
                    //looping to update the size
                    while (SizeUpdate != root) {
                        if (SizeUpdate->parent->left == SizeUpdate) {
                            if (SizeUpdate->parent->leftSize > 0)
                                SizeUpdate->parent->leftSize -= 1;
                        }
                        SizeUpdate = SizeUpdate->parent;
                    }
                    currentNode->parent->right = nullptr;
                    currentNode = nullptr;
                    return true;
                }
            }
            //Size update if the right node is nullptr i.e. empty
            else if (currentNode->right == nullptr) {
                //Deleting the node if when it is root
                if (currentNode->parent == nullptr) {
                    currentNode = currentNode->left;
                    currentNode->left = nullptr;
                    currentNode->right = nullptr;
                    currentNode->leftSize = 0;
                    root = currentNode;
                    return true;
                }
                //Deleting the left node if when it is root
                if (currentNode->parent->left == currentNode) {
                    //Size update
                    while (SizeUpdate != root) {
                        if (SizeUpdate->parent->left == SizeUpdate) {
                            if (SizeUpdate->parent->leftSize > 0)
                                SizeUpdate->parent->leftSize -= 1;
                        }
                        SizeUpdate = SizeUpdate->parent;
                    }
                    //Shifting the nodes
                    currentNode->parent->left = currentNode->left;
                    currentNode = nullptr;
                    return true;
                }
                else if (currentNode->parent->right == currentNode) {
                    //Shifting the nodes
                    while (SizeUpdate != root) {
                        if (SizeUpdate->parent->left == SizeUpdate) {
                            if (SizeUpdate->parent->leftSize > 0)
                                SizeUpdate->parent->leftSize -= 1;
                        }
                        SizeUpdate = SizeUpdate->parent;
                    }

                    currentNode->parent->right = currentNode->left;
                    currentNode = nullptr;
                    return true;
                }
            }
            //Size update if the left node is nullptr i.e. empty
            else if (currentNode->left == nullptr) {
                if (currentNode->parent == nullptr) {
                    currentNode = currentNode->right;
                    currentNode->left = nullptr;
                    currentNode->right = nullptr;
                    currentNode->leftSize = 0;
                    root = currentNode;
                    return true;
                }
                if (currentNode->parent->left == currentNode) {

                    //SizeUpdate
                    while (SizeUpdate != root) {
                        if (SizeUpdate->parent->left == SizeUpdate) {
                            if (SizeUpdate->parent->leftSize > 0)
                                SizeUpdate->parent->leftSize -= 1;
                        }
                        SizeUpdate = SizeUpdate->parent;
                    }
                    currentNode->parent->left = currentNode->right;
                    currentNode = nullptr;
                    return true;
                }
                else if (currentNode->parent->right == currentNode) {


                    //Shifting the nodes.
                    while (SizeUpdate != root) {
                        if (SizeUpdate->parent->left == SizeUpdate) {
                            if (SizeUpdate->parent->leftSize > 0)
                                SizeUpdate->parent->leftSize -= 1;
                        }
                        SizeUpdate = SizeUpdate->parent;
                    }


                    currentNode->parent->right = currentNode->right;
                    currentNode = nullptr;
                    return true;
                }
            }
            //When it has both nodes
            else {
                Node* Replacement = currentNode;
                Replacement = Replacement->right;
                while (Replacement->left != nullptr) {
                    Replacement = Replacement->left;
                }
                double replaceValue = Replacement->key;
                IndexedBST::remove(replaceValue);
                currentNode->key = replaceValue;
                if (rootRemoved) {
                    root->key = replaceValue;
                }
                return true;
            }
        }
        //Going to the right if the the given key is greater than current node key
        else if (key > currentNode->key) {
            currentNode = currentNode->right;
        }
        //Going to the left if the the given key is less than current node key
        else {
            currentNode = currentNode->left;

        }
    }
    return false;
}
