//
// Created by idanh on 13/05/2025.
//

#include <stdio.h>
#include "graph.h"
#include "heap.h"
#include <climits>
#include <iostream>
#include <ostream>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

Graph::Graph(int vertices) {
    numVertices = vertices;
    adjMatrix = new int*[numVertices];
    for (int i = 0; i < numVertices; ++i)
        adjMatrix[i] = new int[numVertices];

    for (int i = 0; i < numVertices; ++i)
        for (int j = 0; j < numVertices; ++j)
            adjMatrix[i][j] = INT_MAX;
}

Graph::~Graph() {
    for (int i = 0; i < numVertices; ++i)
        delete[] adjMatrix[i];
    delete[] adjMatrix;
}
void Graph::addEdge(int u, int v, int weight) {
    adjMatrix[u][v] = weight;
    adjMatrix[v][u] = weight;
}

// Must print MST edges and total weight
void Graph::primMST() {
    int totalWeight = 0;
    unordered_set<string> edges;
    unordered_set<int> visited;
    MinHeap mh(numVertices);

    int currentVertex = 0;
    int edge_weight = 0;
    int prev_v = -1;
    mh.insert(0, 0);

    while (visited.size() < numVertices) { //v
        currentVertex = mh.extractMin(); //O(logV) - will be called (v-1) times throughout the code
        edge_weight = mh.getKey(currentVertex);
        for (int v : visited) { //O(v)
            if (adjMatrix[v][currentVertex] == edge_weight) {
                prev_v = v;
            }
        }
        if (prev_v != -1) {
            edges.insert(to_string(prev_v) + " -- " + to_string(currentVertex) + " | " + to_string(edge_weight)); //O(1)
        }
        visited.insert(currentVertex); //O(1)
        totalWeight += edge_weight;

        for (int v = 0; v < numVertices; ++v) { //v
            int weight = adjMatrix[currentVertex][v];
            if (weight < INT_MAX && !visited.contains(v)) {
                if (mh.isInMinHeap(v)) { //O(1)
                    mh.decreaseKey(v, weight); //O(logV)
                }
                else {
                    mh.insert(v, weight); //O(logV) - Will be called v times throughout the code
                }
            }
        }
        //mh.printArrays();

    }

    cout << "Edges:" << endl;
    for (string edge : edges) {
        cout << edge << endl;
    }
    cout << "Total Weight: " << totalWeight << endl;

}