#include "../include/Prim.h"
#include <iostream>
#include <climits>

Prim::Prim() : graph(nullptr), parent(nullptr), key(nullptr), inMST(nullptr), totalCost(0) {}

Prim::~Prim() {
    delete[] parent;
    delete[] key;
    delete[] inMST;
}

void Prim::run(Graph* graph) {
    this->graph = graph;
    int V = graph->getVertexCount();

    parent = new int[V];
    key = new int[V];
    inMST = new bool[V];

    for (int i = 0; i < V; ++i) {
        key[i] = INT_MAX;
        inMST[i] = false;
        parent[i] = -1;
    }

    key[0] = 0;
    MinHeap heap(V);
    heap.insert(0, 0);

    while (!heap.isEmpty()) {
        VertexDistance* minNode = heap.extractMin();
        int u = minNode->vertex;
        delete minNode;

        if (inMST[u])
            continue;

        inMST[u] = true;

        for (int v = 0; v < V; ++v) {
            if (graph->hasEdge(u, v) && !inMST[v]) {
                int weight = graph->getEdgeWeight(u, v);
                if (weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    if (heap.isInHeap(v)) {
                        heap.decreaseKey(v, weight);
                    } else {
                        heap.insert(v, weight);
                    }
                }
            }
        }
    }

    totalCost = 0;
    for (int i = 1; i < V; ++i) {
        if (parent[i] != -1) {
            totalCost += graph->getEdgeWeight(i, parent[i]);
        }
    }
}

void Prim::displayResult() const {
    int V = graph->getVertexCount();
    std::cout << "MST (Prim):\n";
    for (int i = 1; i < V; ++i) {
        if (parent[i] != -1) {
            std::cout << parent[i] << " - " << i
                      << " (weight: " << graph->getEdgeWeight(i, parent[i]) << ")\n";
        }
    }
    std::cout << "Total cost: " << totalCost << "\n";
}
