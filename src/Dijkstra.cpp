#include "../include/Graph.h"
#include "../include/MinHeap.h"
#include "../include/Timer.h"
#include <iostream>
#include <climits>

double runDijkstraSP(Graph* graph, int src, int dest) {
    int V = graph->getVertexCount();
    int* dist = new int[V];
    int* parent = new int[V];
    bool* visited = new bool[V]();

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }

    dist[src] = 0;
    MinHeap heap(V);
    heap.insert(src, 0);

    Timer timer;
    timer.startTimer();

    while (!heap.isEmpty()) {
        VertexDistance* node = heap.extractMin();
        int u = node->vertex;
        delete node;

        if (u == dest) break;
        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph->hasEdge(u, v)) {
                int weight = graph->getEdgeWeight(u, v);
                if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    heap.isInHeap(v) ? heap.decreaseKey(v, dist[v]) : heap.insert(v, dist[v]);
                }
            }
        }
    }

    timer.stopTimer();
    double duration = timer.getElapsedMilliseconds();

    if (dist[dest] == INT_MAX)
        std::cout << "Brak ścieżki z " << src << " do " << dest << "\n";
    else {
        std::cout << "Dijkstra: " << src << " -> " << dest << ", dystans: " << dist[dest] << "\nŚcieżka: ";
        int* path = new int[V], len = 0, cur = dest;
        while (cur != -1) path[len++] = cur, cur = parent[cur];
        for (int i = len - 1; i >= 0; i--) std::cout << path[i] << (i ? " -> " : "\n");
        delete[] path;
    }

    delete[] dist;
    delete[] parent;
    delete[] visited;
    return duration;
}
