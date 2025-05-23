#include "../include/Graph.h"
#include "../include/MinHeap.h"
#include "../include/Timer.h"

#include <iostream>
#include <climits>  // for INT_MAX

void dijkstraSP(Graph* graph, int src, int dest) {
    int V = graph->getVertexCount();

    int* dist = new int[V];
    int* parent = new int[V];
    bool* visited = new bool[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
        visited[i] = false;
    }

    dist[src] = 0;

    MinHeap minHeap(V);
    minHeap.insert(src, 0);

    while (!minHeap.isEmpty()) {
        VertexDistance* current = minHeap.extractMin();
        int u = current->vertex;
        delete current;

        if (u == dest) break;

        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph->hasEdge(u, v)) {
                int weight = graph->getEdgeWeight(u, v);

                if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;

                    if (minHeap.isInHeap(v)) {
                        minHeap.decreaseKey(v, dist[v]);
                    } else {
                        minHeap.insert(v, dist[v]);
                    }
                }
            }
        }
    }

    if (dist[dest] == INT_MAX) {
        std::cout << "No path from " << src << " to " << dest << std::endl;
    } else {
        std::cout << "Dijkstra's Shortest Path from " << src << " to " << dest << ":\n";
        std::cout << "Total Distance: " << dist[dest] << std::endl;

        std::cout << "Path: ";
        int* path = new int[V];
        int pathLen = 0;
        int current = dest;
        while (current != -1) {
            path[pathLen++] = current;
            current = parent[current];
        }

        for (int i = pathLen - 1; i >= 0; i--) {
            std::cout << path[i];
            if (i > 0) std::cout << " -> ";
        }
        std::cout << std::endl;

        delete[] path;
    }

    delete[] dist;
    delete[] parent;
    delete[] visited;
}

double runDijkstraSP(Graph* graph, int src, int dest) {
    Timer timer;
    timer.startTimer();
    dijkstraSP(graph, src, dest);
    timer.stopTimer();
    return timer.getElapsedMilliseconds();
}
