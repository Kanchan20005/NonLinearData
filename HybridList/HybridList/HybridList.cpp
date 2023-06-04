#include <iostream>
#include <string>
#include <stdexcept>
#include "HybridList.h"
#include <vector>
using namespace std;

HybridList::HybridList() {}

HybridList::HybridList(int blockSize) {
	if (blockSize <= 0)
		throw out_of_range("Invalid block size " + to_string(blockSize));
	this->blockSize = blockSize;
}

HybridList::~HybridList() {
	clear();
}

int HybridList::size() const {
	return numElements;
}

int HybridList::capacity() const {
	return numBlocks * blockSize;
}

int HybridList::block_size() const {
	return blockSize;
}

HybridListNode* HybridList::front() const {
	return head;
}

HybridListNode* HybridList::back() const {
	return tail;
}

double& HybridList::at(int index) const {
	HybridListNode* curNode = head;
	int elementsSearched = 0;

	if (index < 0 || index >= numElements)
		throw out_of_range("Invalid index " + to_string(index));

	// Iterate through all blocks to identify block containing the index
	while (curNode != nullptr) {
		if (index < elementsSearched + curNode->size()) {
			// Element is in this block so just return the correct element from
			// this block
			return curNode->at(index - elementsSearched);
		}
		// Element is not in this block so add the number of elements in the
		// block to the number of elements searched
		elementsSearched += curNode->size();
		curNode = curNode->next;
	}

	// Iterator went beyond last block so something went horribly wrong
	abort();
}

void HybridList::push_back(double value) {
	if (numBlocks == 0) {
		// Hybrid list is empty so creating a new node that will be both the head
		// and tail and append the element to it
		HybridListNode* newTail = new HybridListNode(blockSize);
		newTail->push_back(value);
		tail = newTail;
		head = newTail;
		numBlocks = 1;
	}
	else if (tail->size() == blockSize) {
		// Tail node is full so create a new tail node and copy the back half of
		// the old tail node to the new tail node
		HybridListNode* newTail = new HybridListNode(blockSize);

		// Copy just under half of elements from old tail to new tail
		for (int i = blockSize / 2 + 1; i < blockSize; i++)
			newTail->push_back(tail->at(i));
		tail->resize(blockSize / 2 + 1);
		//cout << tail->size() << endl;
		// Append new item to new tail
		newTail->push_back(value);
		tail->next = newTail;
		//cout << newTail->size() << endl;
		//cout << "Tail: " << tail << endl;
		//cout << "New tail: " << newTail << endl;
		tail = newTail;
		numBlocks++;
	}
	else
		tail->push_back(value);	// Tail isn't full so just append to tail

	numElements++;
}

void HybridList::pop_back() {

	// The HybridList is empty i.e when blocksize is 0 and nead and tail are null pointers
	if (numBlocks == 0) {
		tail->pop_back();
		return;
	}
	//When there is only one node.
	else if (head == tail) {
		//When there is only one element 
		if (numElements == 1) {
			tail->pop_back();
			numElements--;
			numBlocks--;
			head = nullptr;
			tail = nullptr;
		}
		//When there is multiple elements
		else
		{
			tail->pop_back();
			numElements--;

		}
	}
	//When there is 2 nodes
	else if (head->next == tail) 
	{
		//When there is only one element
		if (tail->size() == 1) {
			tail->pop_back();
			tail = head;
			numElements--;
			numBlocks--;

		}
		//When there is multiple elements in second node.
		else
		{
			tail->pop_back();
			numElements--;

		}
	}

	//When there is more than 2 nodes
	else
	{
		HybridListNode* current = head->next;

		//When there is only one element
		if (tail->size() == 1) {

			HybridListNode* new_tail = head->next;

			while (current->next != nullptr) {
				if (current->next = tail)
				{
					new_tail = current;
				}
			}
			tail->pop_back();
			tail = new_tail;
			tail = head;
			numElements--;
			numBlocks--;

		}
		//When there is multiple elements in second node.
		else
		{
			tail->pop_back();
			numElements--;

		}
	}


}

void HybridList::insert(int index, double value) {
	HybridListNode* curNode = head;
	int elementsSearched = 0;
	if (head == nullptr)
	{
		throw std::out_of_range("Array has no elements");
	}
	if (index < 0 || index >= numElements)
		throw out_of_range("Invalid index " + to_string(index));

	// Iterate through all blocks to identify block containing the index
	while (curNode != nullptr) {

		if (index < elementsSearched + curNode->size()) {
			// Element is in this block so just store the current data
			double Current_data = curNode->at(index - elementsSearched);

			//if the Node is full 
			if (curNode->size() == blockSize) {
				// New Node is created to store the new block if the size of the node is full 
				HybridListNode* newNode = new HybridListNode(blockSize);
				HybridListNode* afterCurrNode = new HybridListNode(blockSize);
				afterCurrNode = curNode->next;
				//Copy the elements to be inserted first
				newNode->push_back(value);
				numElements++;
				// Copy just under half of elements from old tail to new tail
				for (int i = blockSize / 2 + 1; i < blockSize; i++)
					newNode->push_back(curNode->at(i));
				curNode->resize(blockSize / 2 + 1);
				//cout << tail->size() << endl;
				// Append new item to new tail
				curNode->next = newNode;
				newNode->next = afterCurrNode;

				numBlocks++;
			}
			//When the node is not full
			else {
				int bs = index - elementsSearched;
				//Pushing back the initial value at the end
				curNode->push_back(value);

				//Swapping the initial value at correct index
				for (int i = bs; i < curNode->size(); i++)
				{
					double temp = curNode->at(i);
					curNode->at(i) = curNode->at(curNode->size() - 1);
					curNode->at(curNode->size() - 1) = temp;
				}
				numElements++;
			}


			break;
		}


		// Element is not in this block so add the number of elements in the
		// block to the number of elements searched
		elementsSearched += curNode->size();
		curNode = curNode->next;
	}
}


void HybridList::erase(int index)
{
	HybridListNode* curNode = head;
	int elementsSearched = 0;
	//Throw error when array has no element
	if (head == nullptr)
	{
		throw std::out_of_range("Array has no elements");
	}
	//Throws error when index is out of bound
	if (index < 0 || index >= numElements) {

	throw out_of_range("Invalid index " + to_string(index));
	}

	// Iterate through all blocks to identify block containing the index
	while (curNode != nullptr) {
		//Checking if the element index lies in the Node
		if (index < elementsSearched + curNode->size()) {
			int bs = index - elementsSearched;
			double Current_data = curNode->at(index - elementsSearched);
			int NodeIndex = index - elementsSearched;
			//This is if the index is at the last element of the block whi
			if (elementsSearched + curNode->size() -1 == index) {
				curNode->at(NodeIndex) = NULL;
				numElements--;

			}
			//For rest of the conditions
			else
			{
				//Looping to check when to swap the elements 
				for (int i = NodeIndex; i <= bs+1 ; i++)
				{

					if (i == blockSize / 2-1)
					{
						curNode->at(i) = curNode->at(i+1);
						curNode->at(i + 1) = curNode->next->at(0);

						break;
					}
					else {
						curNode->at(i) = curNode->at(i + 1);
					}
					
				}
				//if condition based the current node being last or not
				if (curNode->next != nullptr) {
					curNode = curNode->next;
				}
				
				HybridListNode* currentNode = curNode;
				//Looping through rest of the loop to swap the elements.
				while (currentNode != nullptr) {
					for (int i = bs+2; i <= currentNode->size()-2; i++)
					{

						double temp = currentNode->at(i + 1);
						currentNode->at(i) = currentNode->at(i + 1);
						currentNode->at(i + 1);


					}
					currentNode->resize(currentNode->size() - 1);

					currentNode = currentNode->next;
				}
				numElements--;

			}

		


			// Element is not in this block so add the number of elements in the
			// block to the number of elements searched

			break;
		}
		elementsSearched += curNode->size();
		curNode = curNode->next;

	}
	
}


void HybridList::clear() {
	HybridListNode* curNode = head, * nextNode = nullptr;
	// Iterate through each node starting from the head and delete it
	while (curNode != nullptr) {
		nextNode = curNode->next;
		delete curNode;
		curNode = nextNode;
	}
	head = tail = nullptr;
	numElements = numBlocks = 0;
}
