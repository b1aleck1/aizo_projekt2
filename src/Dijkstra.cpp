#include "../include/Dijkstra.h"
#include <climits>
#include <iostream>

int* Dijkstra::distances = nullptr;
int* Dijkstra::previous = nullptr;
int Dijkstra::vertexCount = 0;
int Dijkstra::start = -1;
int Dijkstra::end = -1;

void Dijkstra::run(Graph* graph, int startVertex, int endVertex) {
    start = startVertex;
    end = endVertex;
    vertexCount = graph->getVertexCount();

    int* dist = new int[vertexCount];
    int* prev = new int[vertexCount];
    bool* visited = new bool[vertexCount];

    for (int i = 0; i < vertexCount; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        prev[i] = -1;
    }

    dist[start] = 0;

    for (int count = 0; count < vertexCount - 1; count++) {
        int u = -1, min = INT_MAX;
        for (int v = 0; v < vertexCount; v++)
            if (!visited[v] && dist[v] <= min) {
                min = dist[v];
                u = v;
            }

        if (u == -1) break;
        visited[u] = true;

        for (int v = 0; v < vertexCount; v++) {
            int weight = graph->getEdgeWeight(u, v);
            if (!visited[v] && weight > 0 && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
            }
        }
    }

    distances = dist;
    previous = prev;
    delete[] visited;
}

void Dijkstra::displayResult() const {
    std::cout << "Shortest path from " << start << " to " << end << ": ";
    if (distances[end] == INT_MAX) {
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
