#include "../include/Prim.h"
#include <climits>

void Prim::run(Graph* graph) {
    int V = graph->getVertexCount();
    int* parent = new int[V];
    int* key = new int[V];
    bool* mstSet = new bool[V];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int min = INT_MAX, u = -1;
        for (int v = 0; v < V; v++)
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                u = v;
            }

        mstSet[u] = true;

        for (int v = 0; v < V; v++) {
            int weight = graph->getEdgeWeight(u, v);
            if (weight > 0 && !mstSet[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }
        }
    }

    delete[] parent;
    delete[] key;
    delete[] mstSet;
}

void Prim::displayResult() const {
    // Optional
}
