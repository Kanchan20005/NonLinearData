#include <string>
#include <stdexcept>
#include <iostream>
#include "BoundedArrayConst.h"
using namespace std;

BoundedArrayConst::BoundedArrayConst() {
	for (int i = 0; i < MAX_NUM_ELEMENTS; i++)
		elements[i] = 0;
}

BoundedArrayConst::BoundedArrayConst(int numElements) {
	resize(numElements);

	for (int i = 0; i < MAX_NUM_ELEMENTS; i++)
		elements[i] = 0;
}

BoundedArrayConst::BoundedArrayConst(int numElements, int maxNumElements)
{
	resize(numElements);
	double* elements_new = new double[maxNumElements];//declare new 
	for (int i = 0; i < numElements && i < maxNumElements; i++) {//copy all data
		elements_new[i] = elements[i];
	}
	delete elements;//remove old one
	double* elements = elements_new;//assign new to old
	for (int i = 0; i < maxNumElements; i++)
		elements[i] = 0;
}

BoundedArrayConst::BoundedArrayConst(BoundedArrayConst& b) {
	operator=(b);
}

BoundedArrayConst::~BoundedArrayConst() {}

int BoundedArrayConst::size() {
	return numElements;
}

int BoundedArrayConst::capacity() {
	return MAX_NUM_ELEMENTS;
}

double& BoundedArrayConst::operator[](int index) {
	return elements[index];
}

double& BoundedArrayConst::at(int index) {
	if (index >= numElements)
		throw std::out_of_range("Invalid index " + std::to_string(index));
	return operator[](index);
}

double* BoundedArrayConst::data() {
	return elements;
}




BoundedArrayConst& BoundedArrayConst::operator=(BoundedArrayConst& b) {
	numElements = b.size();
	for (int i = 0; i < numElements; i++)
		elements[i] = b[i];
	for (int i = numElements; i < MAX_NUM_ELEMENTS; i++)
		elements[i] = 0;

	return *this;
}

void BoundedArrayConst::resize(int newSize) {
	if (newSize > MAX_NUM_ELEMENTS || newSize < 0)
		throw std::out_of_range("Invalid size " + std::to_string(newSize));
	numElements = newSize;
}

void BoundedArrayConst::push_back(double value) {
	if (numElements >= MAX_NUM_ELEMENTS)
		throw std::out_of_range("Array has reached its maximum capacity");

	elements[numElements] = value;
	numElements++;
}

void BoundedArrayConst::pop_back() {
	if (numElements == 0)
		throw std::out_of_range("Array has no elements");

	numElements--;
	elements[numElements] = 0;
}

void BoundedArrayConst::insert(int index, double value) {
	if (index >= numElements || index < 0)
		throw std::out_of_range("Invalid index " + std::to_string(index));
	if (numElements >= MAX_NUM_ELEMENTS)
		throw std::out_of_range("Array has reached its maximum capacity");

	for (int i = numElements; i > index; i--)
		elements[i] = elements[i - 1];
	elements[index] = value;
	numElements++;
}

void BoundedArrayConst::erase(int index) {
	if (index >= numElements || index < 0)
		throw std::out_of_range("Invalid index " + std::to_string(index));

	elements[index] = 0;
	for (int i = index; i < numElements - 1; i++)
		elements[i] = elements[i + 1];
	numElements--;
}

void BoundedArrayConst::clear() {
	for (int i = 0; i < numElements; i++)
		elements[i] = 0;
	numElements = 0;
}


int main() {
	BoundedArrayConst Trial(5, 100);
	//for (int i = 0; i < Trial.size(); i++)
	//{
		cout << Trial.at(0) << endl;
//	}
	return 0;
}