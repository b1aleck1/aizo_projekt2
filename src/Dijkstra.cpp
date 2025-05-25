#include "../include/Dijkstra.h"
#include <climits>

void Dijkstra::run(Graph* graph, int startVertex, int endVertex) {
    int V = graph->getVertexCount();
    int* dist = new int[V];
    bool* visited = new bool[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[startVertex] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = -1, min = INT_MAX;
        for (int v = 0; v < V; v++)
            if (!visited[v] && dist[v] <= min) {
                min = dist[v];
                u = v;
            }

        if (u == -1)
            break;

        visited[u] = true;

        for (int v = 0; v < V; v++) {
            int weight = graph->getEdgeWeight(u, v);
            if (!visited[v] && weight > 0 && dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    delete[] dist;
    delete[] visited;
}

void Dijkstra::displayResult() const {
    // Optional
}
