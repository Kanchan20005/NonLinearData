#include "RedBlackTree.h"
#include <algorithm>
#include <iostream>
#include <chrono>
#include <ctime>
using namespace std::chrono;
RedBlackTree::~RedBlackTree() {
    deleteTree(root);
}

void RedBlackTree::deleteTree(RBTNode* node) {
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

//Checking the tree for different validation cases of Red Black Tree
void RedBlackTree::validation(RBTNode* node) {

    //Changing the root to Black
    if (node == root) {
        node->red = false;
        return;
    }

    //Instantiating RBTNode for future calculation
    RBTNode* nodeParent = node->parent;
    RBTNode* grandparent = nodeParent->parent;
    RBTNode* uncle = nullptr;


    if (grandparent != nullptr) {
        if (grandparent->left == nodeParent)
            uncle = grandparent->right;
        if (grandparent->right == nodeParent)
            uncle = grandparent->left;

        //Changing the red uncle to Black when the uncle is red
        //Change color of Parent, Grandparent and Uncle
        if (uncle != nullptr && uncle->red == true) {
            grandparent->red = true;
            nodeParent->red = false;
            uncle->red = false;
        }

        //Changing the Black uncle to red or whatever is needed when the uncle is black
        else if ((uncle != nullptr && uncle->red == false) || uncle == nullptr) {

            //Case 2 When the uncle is black and triangle
            if (node->parent->left == node && nodeParent->parent->right == nodeParent) {
                RotateRight(nodeParent);
            }

            else if (node->parent->right == node && nodeParent->parent->left == nodeParent) {
                RotateLeft(nodeParent);
            }

            //Case 3 When the uncle is black and line
            else if (node->parent->left == node && nodeParent->parent->left == nodeParent) {
                RotateRight(grandparent);
                nodeParent->red = !(nodeParent->red);
                grandparent->red = !(grandparent->red);
            }

            else if (node->parent->right == node && nodeParent->parent->right == nodeParent) {
                RotateLeft(grandparent);
                nodeParent->red = !(nodeParent->red);
                grandparent->red = !(grandparent->red);
            }

        }
    }

    //Case 0 Change root node to black
    root->red = false;
}


//Function for rotating the node of the tree towards left
void RedBlackTree::RotateLeft(RBTNode* node) {
    RBTNode* temp = node->right;
    node->right = temp->left;
    //std::cout << "Rotated Left" << std::endl;
    if (temp->left != nullptr) {
        temp->left->parent = node;
    }
    temp->parent = node->parent;

    if (node->parent == nullptr) {
        root = temp;
    }
    else if (node == node->parent->left) {
        node->parent->left = temp;
    }
    else {
        node->parent->right = temp;
    }
    temp->left = node;
    node->parent = temp;
}

//Function for rotating the node of the tree towards right
void RedBlackTree::RotateRight(RBTNode* node) {

    RBTNode* temp = node->left;
    node->left = temp->right;
    //std::cout << "Rotated Right" << std::endl;

    if (temp->right != nullptr) {
        temp->right->parent = node;
    }
    temp->parent = node->parent;


    if (node->parent == nullptr) {
        root = temp;
    }
    else if (node == node->parent->left) {
        node->parent->left = temp;
    }
    else {
        node->parent->right = temp;
    }

    temp->right = node;
    node->parent = temp;

}



int RedBlackTree::Height(RBTNode* node) {
    if (node == nullptr)
        return -1;
    else
    {
        int leftHeight = Height(node->left);
        int rightHeight = Height(node->right);

        /* use the larger one */
        if (leftHeight > rightHeight)
            return(leftHeight + 1);
        else return(rightHeight + 1);
    }

}

int RedBlackTree::Height() {
    RBTNode* node = root;
    if (node == nullptr)
        return -1;
    else
    {
        int leftHeight = Height(node->left);
        int rightHeight = Height(node->right);

        /* use the larger one */
        if (leftHeight > rightHeight)
            return(leftHeight + 1);
        else return(rightHeight + 1);
    }

}



//Function for insertion of node in RedBlack Tree
void RedBlackTree::insert(RBTNode* node) {
    if (root == nullptr) {
        root = node;
        node->parent = nullptr;
        return;
    }

    RBTNode* cur = root;
    while (cur != nullptr) {
        if (node->key < cur->key) {
            if (cur->left == nullptr) {
                cur->left = node;
                node->parent = cur;
                cur = nullptr;
            }
            else
                cur = cur->left;
        }
        else {
            if (cur->right == nullptr) {
                cur->right = node;
                node->parent = cur;
                cur = nullptr;
            }
            else
                cur = cur->right;
        }
    }

    if (node != nullptr) {
        if (node == root) {
            validation(node);
        }
        while (node->parent != nullptr) {
            RBTNode* temp = node->parent;
            if (node->parent->red && node->red) {
                validation(node);
            }
            node = temp;
        }
    }
}



/*
int main() {

    RedBlackTree b;

    const int N = 10000;
    double array[N];
    for (int i = 0; i < N; i++) {
        double r = ((double)rand() / (RAND_MAX));
        array[i] = r;
    }

    int array1[N / 2]; // Declare the array with half the size of N
    int a = 0;
    for (int i = N/4; i < (N-N / 4); i++) {

        array1[a] = array[i]; // Populate the array with values from 0 to N/2-1
        a++;
    }


    int array0[N / 4]; // Declare the array with half the size of N

    for (int i = 0; i < N/4; i++) {
        array0[i] = array[i]; // Populate the array with values from 0 to N/2-1
    }

    int array2[N / 4]; // Declare the array with half the size of N

    for (int i = N-N/4; i < N; i++) {
        array2[i] = array[i]; // Populate the array with values from 0 to N/2-1
    }

    int size1 = sizeof(array0) / sizeof(array0[0]);
    int size2 = sizeof(array2) / sizeof(array2[0]);

    int m = sizeof(array1) / sizeof(array1[0]);


    std::sort(array1,array1+m);

    double Finalarray[N];

    std::copy(array0, array0 + size1, Finalarray);
    std::copy(array1, array1 + m, Finalarray + size1);
    std::copy(array2, array2 + size2, Finalarray + size1+m);


    auto start = steady_clock::now();
    for (int i = 0; i < N; i++) {
        RBTNode* bRoot;
  
            b.insert(new RBTNode(Finalarray[i]));

    }

    /*for (int i = 0; i < 1000; i++) {
       RBTNode* bRoot;
       double r;
        if (i == 0)
        {    
             bRoot = new RBTNode((double)rand() / (RAND_MAX));
             b.insert(bRoot);
            
        }
        else {
            r = ((double)rand() / (RAND_MAX));
            b.insert(new RBTNode(r));


        }

    }
    */
/*
    auto duration = steady_clock::now() - start;
    std::cout << "Duration " << duration_cast<milliseconds>(duration).count() << std::endl;

    std::cout << "Height " << b.Height() << std::endl;





}
*/