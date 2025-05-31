#include "../include/Dijkstra.h"
#include <iostream>

int* Dijkstra::distances = nullptr;
int* Dijkstra::previous = nullptr;
int Dijkstra::vertexCount = 0;
int Dijkstra::start = -1;
int Dijkstra::end = -1;

// --- Implementacja MinHeap ---

void Dijkstra::MinHeap::swap(int i, int j) {
    int temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
    pos[heap[i]] = i;
    pos[heap[j]] = j;
}

void Dijkstra::MinHeap::heapifyDown(int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && dist[heap[left]] < dist[heap[smallest]])
        smallest = left;
    if (right < size && dist[heap[right]] < dist[heap[smallest]])
        smallest = right;

    if (smallest != i) {
        swap(i, smallest);
        heapifyDown(smallest);
    }
}

void Dijkstra::MinHeap::heapifyUp(int i) {
    int parent = (i - 1) / 2;
    if (i && dist[heap[i]] < dist[heap[parent]]) {
        swap(i, parent);
        heapifyUp(parent);
    }
}

Dijkstra::MinHeap::MinHeap(int capacity, int* dist)
    : capacity(capacity), size(0), dist(dist) {
    heap = new int[capacity];
    pos = new int[capacity];
    for (int i = 0; i < capacity; i++)
        pos[i] = -1;
}

Dijkstra::MinHeap::~MinHeap() {
    delete[] heap;
    delete[] pos;
}

void Dijkstra::MinHeap::insert(int v) {
    heap[size] = v;
    pos[v] = size;
    size++;
    heapifyUp(size - 1);
}

bool Dijkstra::MinHeap::empty() const {
    return size == 0;
}

int Dijkstra::MinHeap::extractMin() {
    if (empty()) return -1;
    int root = heap[0];
    heap[0] = heap[size - 1];
    pos[heap[0]] = 0;
    size--;
    heapifyDown(0);
    pos[root] = -1;
    return root;
}

void Dijkstra::MinHeap::decreaseKey(int v) {
    int i = pos[v];
    heapifyUp(i);
}

bool Dijkstra::MinHeap::contains(int v) const {
    return pos[v] != -1;
}

// --- Koniec implementacji MinHeap ---

Dijkstra::~Dijkstra() {
    if (distances != nullptr) {
        delete[] distances;
        distances = nullptr;
    }
    if (previous != nullptr) {
        delete[] previous;
        previous = nullptr;
    }
}

void Dijkstra::run(Graph* graph, int startVertex, int endVertex) {
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

    MinHeap minHeap(vertexCount, dist);
    for (int i = 0; i < vertexCount; i++)
        minHeap.insert(i);

    while (!minHeap.empty()) {
        int u = minHeap.extractMin();
        if (u == -1 || dist[u] == INT_MAX) break;

        for (int v = 0; v < vertexCount; v++) {
            int weight = graph->getEdgeWeight(u, v);
            if (weight > 0 && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                if (minHeap.contains(v))
                    minHeap.decreaseKey(v);
            }
        }
    }

    if (distances != nullptr) delete[] distances;
    if (previous != nullptr) delete[] previous;
    distances = dist;
    previous = prev;
}

void Dijkstra::displayResult() const {
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
