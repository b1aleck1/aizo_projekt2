#include "../include/Graph.h"
#include "../include/Timer.h"

#include <iostream>
#include <climits>

// Implementation of Prim's algorithm for MST
void primMST(Graph* graph, int* parent, int* key) {
    int V = graph->getVertexCount();
    bool* mstSet = new bool[V];

    // Initialize all keys as infinite and mstSet as false
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    // Include first vertex in MST
    key[0] = 0;     // Make key 0 so that this vertex is picked first
    parent[0] = -1; // First node is always root of MST

    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = -1;
        int min = INT_MAX;

        for (int v = 0; v < V; v++) {
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                u = v;
            }
        }

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of adjacent vertices
        for (int v = 0; v < V; v++) {
            int weight = graph->getEdgeWeight(u, v);
            if (weight > 0 && !mstSet[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }
        }
    }

    delete[] mstSet;
}
