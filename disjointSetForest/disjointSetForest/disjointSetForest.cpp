#include <vector>
#include <iostream>
#include <string>

#include <chrono>


class Node {
public:
	int value = 0;
	int rank = 0;
	Node* parent = nullptr;
	Node(int value) { this->value = value; }
};

void makeSet(Node* element);
Node* findSet(Node* element, bool pathCompression);
void unionSet(Node* element1, Node* element2, bool unionByRank, bool pathCompression);
void Link(Node* element1, Node* element2);
void printAllElements(std::vector<Node*> elements);
double checkTimeWorst(bool unionByRank, bool pathCompression, int numElements);
double checkTimeAvg(bool unionByRank, bool pathCompression, int numElements);



void makeSet(Node* element) {
	element->parent = element;
	element->rank = 0;
}

//implemented path compression
Node* findSet(Node* element, bool pathCompression) {
	if (element != element->parent) {
		if (pathCompression) {
			element->parent = findSet(element->parent, pathCompression);
			return element->parent;
		}
		else {
			findSet(element->parent, pathCompression);
			element = element->parent;
			//return element->parent;
		}
	}
	element = element->parent;
	return element->parent;
}


void unionSet(Node* element1, Node* element2, bool unionByRank, bool pathCompression) {

	//Link(findSet(element1, pathCompression), findSet(element2, pathCompression));
	if (!unionByRank) {
		findSet(element1, pathCompression)->parent = findSet(element2, pathCompression)->parent;
	}
	else {
		Link(findSet(element1, pathCompression), findSet(element2, pathCompression));
	}
}

void Link(Node* element1, Node* element2) {
	if (element1->rank > element2->rank) {
		element2->parent = element1;
	}
	else {
		element1->parent = element2;
		if (element1->rank == element2->rank) {
			element2->rank = element2->rank + 1;
		}
	}
}


void printAllElements(std::vector<Node*> elements) {
	std::cout << "Element  Parent  Set Representative" << std::endl;
	for (int i = 0; i < elements.size(); i++) {
		std::cout << elements.at(i)->value << "  "
			<< elements.at(i)->parent->value << "  "
			<< findSet(elements.at(i), false)->value << std::endl;
	}
}


int main() {

	std::cout << "Worst Case " << std::endl;
	std::cout << "Time in microsecond without both heruistic: " << std::endl;
	std::cout << checkTimeWorst(false, false, 100) << std::endl;
	std::cout << checkTimeWorst(false, false, 1000) << std::endl;
	std::cout << checkTimeWorst(false, false, 10000) << std::endl;
	std::cout << "Time in microsecond with both heruistic: " << std::endl;
	std::cout << checkTimeWorst(true, true, 100) << std::endl;
	std::cout << checkTimeWorst(true, true, 1000) << std::endl;
	std::cout << checkTimeWorst(true, true, 10000) << std::endl;



	std::cout << "Average Case " << std::endl;
	std::cout << "Time in microsecond with unionByRank heruistic: " << std::endl;
	std::cout << checkTimeAvg(true, false, 1000) << std::endl;
	std::cout << checkTimeAvg(true, false, 10000) << std::endl;
	std::cout << checkTimeAvg(true, false, 100000) << std::endl;
	std::cout << checkTimeAvg(true, false, 1000000) << std::endl;

	std::cout << "Time in microsecond with pathCompression heruistic: " << std::endl;
	std::cout << checkTimeAvg(false, true, 1000) << std::endl;
	std::cout << checkTimeAvg(false, true, 10000) << std::endl;
	std::cout << checkTimeAvg(false, true, 100000) << std::endl;
	std::cout << checkTimeAvg(false, true, 1000000) << std::endl;

	std::cout << "Time in microsecond with both heruistic: " << std::endl;
	std::cout << checkTimeAvg(false, true, 1000) << std::endl;
	std::cout << checkTimeAvg(false, true, 10000) << std::endl;
	std::cout << checkTimeAvg(false, true, 100000) << std::endl;
	std::cout << checkTimeAvg(false, true, 1000000) << std::endl;

	return 0;
}

double checkTimeWorst(bool unionByRank, bool pathCompression, int numElements) {
	std::vector<Node*> elements(numElements);
	for (int i = 0; i < numElements; i++)
		elements.at(i) = new Node(i);
	for (int i = 0; i < numElements; i++) {
		makeSet(elements.at(i));
	}

	auto begin = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < numElements; i++) {
		unionSet(elements.at(0), elements.at(i), unionByRank, pathCompression);
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	return (double)elapsed.count() / (double)1000;
}

double checkTimeAvg(bool unionByRank, bool pathCompression, int numElements) {
	std::vector<Node*> elements(numElements);
	for (int i = 0; i < numElements; i++)
		elements.at(i) = new Node(i);

	for (int i = 0; i < numElements; i++) {
		makeSet(elements.at(i));
	}

	auto begin = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < numElements; i++) {
		unionSet(elements.at(rand() % 100 + 1), elements.at(rand() % 100 + 1), unionByRank, pathCompression);
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	return (double)elapsed.count() / (double)1000;
}