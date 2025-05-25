#include "../include/BellmanFord.h"
#include <climits>

void BellmanFord::run(Graph* graph, int startVertex, int endVertex) {
    int V = graph->getVertexCount();
    int* dist = new int[V];

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;

    dist[startVertex] = 0;

    for (int i = 1; i < V; i++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                int weight = graph->getEdgeWeight(u, v);
                if (weight != 0 && dist[u] != INT_MAX && dist[u] + weight < dist[v])
                    dist[v] = dist[u] + weight;
            }
        }
    }

    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            int weight = graph->getEdgeWeight(u, v);
            if (weight != 0 && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                delete[] dist;
                return;
            }
        }
    }

    delete[] dist;
}

void BellmanFord::displayResult() const {
    // Optional
}
