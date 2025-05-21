#include "../include/Graph.h"
#include "../include/Timer.h"

#include <iostream>

// Structure to store vertex and distance pair
struct VertexDistance {
    int vertex;
    int distance;

    VertexDistance(int v, int d) : vertex(v), distance(d) {}

    // For priority queue comparison
    bool operator>(const VertexDistance& other) const {
        return distance > other.distance;
    }
};

// Implementation of Min Heap for Dijkstra's algorithm
class MinHeap {
private:
    VertexDistance** heap;
    int* position;  // To store positions of vertices in heap
    int heapSize;
    int capacity;

public:
    MinHeap(int capacity) {
        this->capacity = capacity;
        heapSize = 0;
        heap = new VertexDistance*[capacity];
        position = new int[capacity];

        // Initialize positions
        for (int i = 0; i < capacity; i++) {
            position[i] = -1; // -1 means not in heap
        }
    }

    ~MinHeap() {
        for (int i = 0; i < heapSize; i++) {
            delete heap[i];
        }
        delete[] heap;
        delete[] position;
    }

    bool isEmpty() {
        return heapSize == 0;
    }

    void swap(int a, int b) {
        VertexDistance* temp = heap[a];
        heap[a] = heap[b];
        heap[b] = temp;

        position[heap[a]->vertex] = a;
        position[heap[b]->vertex] = b;
    }

    void minHeapify(int idx) {
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < heapSize && heap[left]->distance < heap[smallest]->distance) {
            smallest = left;
        }

        if (right < heapSize && heap[right]->distance < heap[smallest]->distance) {
            smallest = right;
        }

        if (smallest != idx) {
            swap(idx, smallest);
            minHeapify(smallest);
        }
    }

    VertexDistance* extractMin() {
        if (isEmpty()) {
            return nullptr;
        }

        VertexDistance* root = heap[0];
        VertexDistance* lastNode = heap[heapSize - 1];

        heap[0] = lastNode;
        position[root->vertex] = -1;
        position[lastNode->vertex] = 0;

        heapSize--;
        minHeapify(0);

        return root;
    }

    void decreaseKey(int vertex, int newDistance) {
        int idx = position[vertex];
        heap[idx]->distance = newDistance;

        // Bubble up if needed
        while (idx > 0 && heap[idx]->distance < heap[(idx - 1) / 2]->distance) {
            swap(idx, (idx - 1) / 2);
            idx = (idx - 1) / 2;
        }
    }

    bool isInHeap(int vertex) {
        return position[vertex] != -1;
    }

    void insert(int vertex, int distance) {
        VertexDistance* newNode = new VertexDistance(vertex, distance);
        heap[heapSize] = newNode;
        position[vertex] = heapSize;

        // Fix heap property if violated
        int i = heapSize;
        heapSize++;

        while (i > 0 && heap[i]->distance < heap[(i - 1) / 2]->distance) {
            swap(i, (i - 1) / 2);
            i = (i - 1) / 2;
        }
    }
};

// Implementation of Dijkstra's algorithm
void dijkstraSP(Graph* graph, int src, int dest) {
    int V = graph->getVertexCount();

    // Distance array and parent array
    int* dist = new int[V];
    int* parent = new int[V];
    bool* visited = new bool[V];

    // Initialize
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
        visited[i] = false;
    }

    dist[src] = 0;

    // Min heap to extract minimum distance vertex
    MinHeap minHeap(V);
    minHeap.insert(src, 0);

    while (!minHeap.isEmpty()) {
        VertexDistance* current = minHeap.extractMin();
        int u = current->vertex;
        delete current;

        if (u == dest) break;  // Stop if destination reached

        visited[u] = true;

        // Update distances of all adjacent vertices
        for (int v = 0; v < V; v++) {
            if (graph->hasEdge(u, v)) {
                int weight = graph->getEdgeWeight(u, v);

                // If v is not visited and path through u is better
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

    // Print the shortest path
    if (dist[dest] == INT_MAX) {
        std::cout << "No path from " << src << " to " << dest << std::endl;
    } else {
        std::cout << "Dijkstra's Shortest Path from " << src << " to " << dest << ":\n";
        std::cout << "Total Distance: " << dist[dest] << std::endl;

        // Print the path
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

// Function to run Dijkstra's algorithm with time measurement
double runDijkstraSP(Graph* graph, int src, int dest) {
    Timer timer;

    timer.startTimer();
    dijkstraSP(graph, src, dest);
    timer.stopTimer();

    return timer.getElapsedMilliseconds();
}
