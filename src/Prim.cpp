#include "../include/Graph.h"
#include "../include/Timer.h"
#include <iostream>
#include <climits>

double runPrimMST(Graph* graph) {
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

    Timer timer;
    timer.startTimer();

    for (int count = 0; count < V - 1; count++) {
        int u = -1, min = INT_MAX;
        for (int v = 0; v < V; v++)
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                u = v;
            }

        if (u == -1) break;
        mstSet[u] = true;

        for (int v = 0; v < V; v++) {
            int weight = graph->getEdgeWeight(u, v);
            if (weight > 0 && !mstSet[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }
        }
    }

    timer.stopTimer();
    double duration = timer.getElapsedMilliseconds();

    for (int i = 1; i < V; i++)
        std::cout << parent[i] << " - " << i << " (waga: " << graph->getEdgeWeight(parent[i], i) << ")\n";

    delete[] parent;
    delete[] key;
    delete[] mstSet;
    return duration;
}
