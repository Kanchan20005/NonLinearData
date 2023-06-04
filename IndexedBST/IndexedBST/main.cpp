// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "IndexedBST.h"
using namespace std;

void testSearch(IndexedBST* tree, double key);
void testAt(IndexedBST* tree, int index);

int main()
{
    // Test insert
    double numbers[] = { 9, 4, 11, 2, 6, 15, 1, 3, 5, 8, 0 };
    IndexedBST* tree = new IndexedBST();
    for (double number : numbers) {
        tree->insert(new Node(number));
    }

    double key;
    cout << "Enter key to search for: ";
    cin >> key;
    testSearch(tree, key);

    int index;
    cout << "Enter index: ";
    cin >> index;
    testAt(tree, index);

    // Test remove
    double keyToRemove;
    cout << endl << "Enter key to remove: ";
    cin >> keyToRemove;
    bool keyRemoved = tree->remove(keyToRemove);
    cout << "Removed key " << keyToRemove << "?: " << keyRemoved << endl;
    testSearch(tree, key);
    testAt(tree, index);

    return 0;
}

void testSearch(IndexedBST* tree, double key) {
    Node* foundNode = tree->search(key);
    if (foundNode != nullptr) {
        cout << "Found node with key = " << foundNode->key << endl;
        cout << "Left size = " << foundNode->leftSize << endl;
        if (foundNode->parent != nullptr) {
            cout << "Parent node key = " << foundNode->parent->key << endl;
            cout << "Left size = " << foundNode->parent->leftSize << endl;
        }
        if (foundNode->left != nullptr) {
            cout << "Left child node key = " << foundNode->left->key << endl;
            cout << "Left size = " << foundNode->left->leftSize << endl;
        }
        if (foundNode->right != nullptr) {
            cout << "Right child node key = " << foundNode->right->key << endl;
            cout << "Left size = " << foundNode->right->leftSize << endl;
        }
    }
    else
        cout << "Key " << key << " not found." << endl;
}

void testAt(IndexedBST* tree, int index) {
    Node* foundNode = tree->at(index);
    if (foundNode != nullptr) {
        cout << "Found node with key = " << foundNode->key << endl;
        cout << "Left size = " << foundNode->leftSize << endl;
    }
    else
        cout << "Index " << index << " not found." << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file