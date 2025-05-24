#include "../include/Graph.h"
#include "../include/Timer.h"
#include <iostream>
#include <climits>

struct Edge {
    int src, dest, weight;
};

double runBellmanFordSP(Graph* graph, int src, int dest) {
    int V = graph->getVertexCount(), E = graph->getEdgeCount();
    Edge* edges = new Edge[E];
    int idx = 0;

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            if (graph->hasEdge(i, j))
                edges[idx++] = { i, j, graph->getEdgeWeight(i, j) };

    int* dist = new int[V];
    int* parent = new int[V];
    for (int i = 0; i < V; i++) dist[i] = INT_MAX, parent[i] = -1;
    dist[src] = 0;

    Timer timer;
    timer.startTimer();

    for (int i = 1; i < V; i++)
        for (int j = 0; j < E; j++) {
            int u = edges[j].src, v = edges[j].dest, w = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }

    for (int i = 0; i < E; i++)
        if (dist[edges[i].src] != INT_MAX && dist[edges[i].src] + edges[i].weight < dist[edges[i].dest]) {
            std::cout << "Wykryto cykl o ujemnej wadze.\n";
            delete[] edges; delete[] dist; delete[] parent;
            return timer.getElapsedMilliseconds();
        }

    timer.stopTimer();
    double duration = timer.getElapsedMilliseconds();

    if (dist[dest] == INT_MAX)
        std::cout << "Brak ścieżki z " << src << " do " << dest << "\n";
    else {
        std::cout << "Bellman-Ford: " << src << " -> " << dest << ", dystans: " << dist[dest] << "\nŚcieżka: ";
        int* path = new int[V], len = 0, cur = dest;
        while (cur != -1) path[len++] = cur, cur = parent[cur];
        for (int i = len - 1; i >= 0; i--) std::cout << path[i] << (i ? " -> " : "\n");
        delete[] path;
    }

    delete[] edges;
    delete[] dist;
    delete[] parent;
    return duration;
}
