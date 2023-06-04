#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <forward_list>


int main() {
	//Reading the file
	std::string Lines;
	std::ifstream my_file;
	my_file.open("facebook-links.txt");
	if (!my_file.is_open()) {
		std::cout << "Cannot open the file";
		return EXIT_FAILURE;
	}

	std::unordered_map<int, std::forward_list<int>> faceBookGraph;
	//Looping through each line in the file
	while (getline(my_file, Lines)) {
		std::istringstream Stream(Lines);
		std::string Firstcol, Secondcol;
		Stream >> Firstcol >> Secondcol;
		int FirstPerson = stoi(Firstcol);
		int SecondPerson = stoi(Secondcol);

		auto position = faceBookGraph.find(FirstPerson);

		//Adding the node in the graph if the first person is not present
		if (position == faceBookGraph.end()) {
			std::forward_list<int> vertex;
			vertex.push_front(SecondPerson);
			faceBookGraph.insert(std::make_pair(FirstPerson, vertex));
		}
		else {
			//If it lies in the graph
			bool present = false;
			//Adding the edge of the first person to connect to the second person if it does not exist
			for (int& Secondcol : position->second) {
				if (Secondcol == SecondPerson) 
					{
					present = true; 
				}
			}
			//Creating the pair for edge foe later use if it does not exist
			if (!present) {
				position->second.push_front(SecondPerson);
			}
		}
		//Adding the node in the graph if the second person is not present
		position = faceBookGraph.find(SecondPerson);
		//Creating a pair if the secondPerson is not present in the graph and inserting the pair
		if (position == faceBookGraph.end()) {
			std::forward_list<int> node;
			node.push_front(FirstPerson);
			faceBookGraph.insert(std::make_pair(SecondPerson, node));
		}
		else {
			//If the second person is in the graph creating the edge.
			bool contains = false;
			for (int& Secondcol : position->second) {
				if (Secondcol == FirstPerson) { contains = true; }
			}
			if (!contains) {
				position->second.push_front(FirstPerson);
			}
		}
	}

	//This section of the code is the calculation for desired output
	int Count = 0;
	int Degree = 0;
	int DegreeG100Count = 0;

	//Complete loop through the graph visiting each vertices
	for (auto itr = faceBookGraph.begin(); itr != faceBookGraph.end(); itr++)
	{
		int degreeG100 = 0;
		Count++;
		//Counting the degree for each value and the total degree of the graph
		for (int& Secondcol : itr->second) {
			degreeG100++;
			Degree++;
		}
		//incrementing the count for vertex with degree greater than 100
		if (degreeG100 >= 100) {
			DegreeG100Count++;
		}
	}

	double average = (Degree / (double)Count);
	std::cout << "The average degree over all vertices in the graph is " << average << std::endl;
	std::cout << "The number of vertices with degree greater than 100 is " << DegreeG100Count;
	return 0;
}