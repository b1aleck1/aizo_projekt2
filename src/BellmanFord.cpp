#include "../include/BellmanFord.h"
#include <climits>
#include <iostream>

int* BellmanFord::distances = nullptr;
int* BellmanFord::previous = nullptr;
int BellmanFord::vertexCount = 0;
int BellmanFord::start = -1;
int BellmanFord::end = -1;

void BellmanFord::run(Graph* graph, int startVertex, int endVertex) {
    start = startVertex;
    end = endVertex;
    vertexCount = graph->getVertexCount();

    int* dist = new int[vertexCount];
    int* prev = new int[vertexCount];

    for (int i = 0; i < vertexCount; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }

    dist[start] = 0;

    for (int i = 0; i < vertexCount - 1; i++) {
        for (int u = 0; u < vertexCount; u++) {
            for (int v = 0; v < vertexCount; v++) {
                int weight = graph->getEdgeWeight(u, v);
                if (weight != 0 && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                }
            }
        }
    }

    // Check for negative weight cycle
    for (int u = 0; u < vertexCount; u++) {
        for (int v = 0; v < vertexCount; v++) {
            int weight = graph->getEdgeWeight(u, v);
            if (weight != 0 && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                std::cerr << "Graph contains a negative-weight cycle\n";
                delete[] dist;
                delete[] prev;
                distances = nullptr;
                previous = nullptr;
                return;
            }
        }
    }

    distances = dist;
    previous = prev;
}

void BellmanFord::displayResult() const {
    std::cout << "Shortest path from " << start << " to " << end << ": ";
    if (distances == nullptr || distances[end] == INT_MAX) {
        std::cout << "NO PATH\n";
        return;
    }

    std::cout << distances[end] << "\nPath: ";

    int* path = new int[vertexCount];
    int temp = end;
    int length = 0;

    while (temp != -1) {
        path[length++] = temp;
        temp = previous[temp];
    }

    for (int i = length - 1; i >= 0; i--) {
        std::cout << path[i];
        if (i > 0) std::cout << " -> ";
    }
    std::cout << "\n";

    delete[] path;
}
