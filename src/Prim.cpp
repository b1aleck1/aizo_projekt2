#include "../include/Prim.h"
#include <climits>
#include <iostream>

int* Prim::mstParent = nullptr;
int Prim::totalWeight = 0;
int Prim::vertexCount = 0;

void Prim::run(Graph* graph) {
    vertexCount = graph->getVertexCount();
    int* key = new int[vertexCount];
    bool* mstSet = new bool[vertexCount];
    int* parent = new int[vertexCount];

    for (int i = 0; i < vertexCount; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
        parent[i] = -1;
    }

    key[0] = 0;

    for (int count = 0; count < vertexCount - 1; count++) {
        int u = -1, min = INT_MAX;
        for (int v = 0; v < vertexCount; v++)
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                u = v;
            }

        mstSet[u] = true;

        for (int v = 0; v < vertexCount; v++) {
            int weight = graph->getEdgeWeight(u, v);
            if (weight > 0 && !mstSet[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }
        }
    }

    totalWeight = 0;
    for (int i = 1; i < vertexCount; i++) {
        totalWeight += graph->getEdgeWeight(parent[i], i);
    }

    mstParent = parent;
    delete[] key;
    delete[] mstSet;
}

void Prim::displayResult() const {
    std::cout << "Edges MST (Prim):\n";
    for (int i = 1; i < vertexCount; i++) {
        std::cout << mstParent[i] << " - " << i << "\n";
    }
    std::cout << "Total cost: " << totalWeight << "\n";
}
