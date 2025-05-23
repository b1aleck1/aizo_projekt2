#include "../include/Graph.h"
#include "../include/Timer.h"
#include "../include/MinHeap.h"

#include <iostream>
#include <climits>

// Deklaracja funkcji pomocniczej
void primMST(Graph* graph, int* parent, int* key);

// Definicja funkcji wywoływanej z main.cpp
double runPrimMST(Graph* graph) {
    int V = graph->getVertexCount();
    int* parent = new int[V];
    int* key = new int[V];

    Timer timer;
    timer.startTimer();

    primMST(graph, parent, key);

    timer.stopTimer();
    double duration = timer.getElapsedMilliseconds();

    // Debug: Wypisz krawędzie MST (opcjonalne)

    for (int i = 1; i < V; i++) {
        std::cout << parent[i] << " - " << i << " (waga: "
                  << graph->getEdgeWeight(parent[i], i) << ")\n";
    }

    delete[] parent;
    delete[] key;

    return duration;
}

// Właściwa implementacja algorytmu Prima
void primMST(Graph* graph, int* parent, int* key) {
    int V = graph->getVertexCount();
    bool* mstSet = new bool[V];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = -1;
        int min = INT_MAX;

        for (int v = 0; v < V; v++) {
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                u = v;
            }
        }

        if (u == -1) break; // brak dostępnych wierzchołków

        mstSet[u] = true;

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
