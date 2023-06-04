// facebookGraph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <queue>
#include <chrono>
const std::string FACEBOOK_FILENAME = "facebook-links.txt";
const int DEGREE_CUTOFF = 100;

void addEdge(std::vector<std::unordered_set<int>>& adjList, int u, int v);
std::vector<int> GraphTopologicalSort(std::vector<std::unordered_set<int>>& graph);
int GraphGetIncomingEdgeCount(std::vector<std::unordered_set<int>>& edgeList, int vertex);

int main()
{
    std::ifstream inFS;
    std::cout << "Opening file " << FACEBOOK_FILENAME << std::endl;
    inFS.open(FACEBOOK_FILENAME);
    if (!inFS.is_open()) {
        std::cout << "Could not open file " << FACEBOOK_FILENAME << std::endl;
        return 1;
    }

    // Read in edge line by line and add edges
    std::vector<std::unordered_set<int>> facebookAdjList;
    int u, v, lineNum = 0;
    std::string timestamp;
    while (!inFS.eof()) {
        //for (int i = 0; i < 100; i++) {
        lineNum++;
        if (lineNum % 100000 == 0)
            std::cout << "Reading line " << lineNum << std::endl;

        inFS >> u >> v >> timestamp;
        if (!inFS.fail())
            addEdge(facebookAdjList, u, v);
    }
    inFS.close();

    // Compute degree statistics over all vertices
    int numVertices = facebookAdjList.size();
    double meanDegree = 0;
    int numDegAtLeastCutoff = 0;
    for (int i = 0; i < facebookAdjList.size(); i++) {
        int vertexDeg = facebookAdjList.at(i).size();
        if (vertexDeg >= DEGREE_CUTOFF)
            numDegAtLeastCutoff++;
        if (vertexDeg >= 0)
            meanDegree += vertexDeg / (double)numVertices;
        //std::cout << "Vertex " << i << " has degree " << vertexDeg << std::endl;
    }

    std::cout << "Mean degree: " << meanDegree << std::endl;
    std::cout << "Number of vertices with degree >= " << DEGREE_CUTOFF
        << ": " << numDegAtLeastCutoff << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();

    // Call the function
    GraphTopologicalSort(facebookAdjList);

    // Stop the timer
    auto end_time = std::chrono::high_resolution_clock::now();

    // Calculate the duration in milliseconds
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    // Print the duration in milliseconds
    std::cout << "Function duration: " << duration_ms.count() << " ms" << std::endl;
    std::cout << "Count: " << GraphGetIncomingEdgeCount(facebookAdjList,500) << std::endl;

    return 0;
}

void addEdge(std::vector<std::unordered_set<int>>& adjList, int u, int v) {
    // If either node is not already in the outer list, then add it
    if (std::max(u, v) >= adjList.size())
        adjList.resize(std::max(u, v) + 1);

    // Check if v is already in the inner set for node u, and if not, add it,
    // and vice versa
    if (adjList.at(u).count(v) == 0)
        adjList.at(u).insert(v);
    if (adjList.at(v).count(u) == 0)
        adjList.at(v).insert(u);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu




std::vector<int> GraphTopologicalSort(std::vector<std::unordered_set<int>>& graph) {
    // Calculate in-degrees for each vertex
    std::vector<int> inDegree(graph.size(), 0);
    for (int i = 0; i < graph.size(); i++) {
        for (auto neighbor : graph[i]) {
            inDegree[neighbor]++;
            //std::cout << "sum" << std::endl;
        }
    }
    std::cout << inDegree.size() << std::endl;


    // Initialize a set with all vertices that have zero in-degree
    std::unordered_set<int> noIncoming;
    for (int i = 0; i < inDegree.size(); i++) {
        noIncoming.insert(i);
    }

    // Perform topological sort
    std::vector<int> result;
    while (!noIncoming.empty()) {
        int currentV = *noIncoming.begin();
        noIncoming.erase(noIncoming.begin());
        result.push_back(currentV);
        for (auto neighbor : graph[currentV]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                noIncoming.insert(neighbor);
            }
        }
    }

    return result;
}
int GraphGetIncomingEdgeCount(std::vector<std::unordered_set<int>>& edgeList, int vertex) {
    int count = 0;
    for (auto& edges : edgeList) {
        if (edges.find(vertex) != edges.end()) {
            count++;
        }
    }
    return count;
}

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file