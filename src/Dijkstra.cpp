#include "../include/Dijkstra.h"
#include <iostream>
#include <climits>

// Statyczne pola przechowujące wyniki i stan
int* Dijkstra::distances = nullptr;
int* Dijkstra::previous = nullptr;
int Dijkstra::vertexCount = 0;
int Dijkstra::start = -1;
int Dijkstra::end = -1;

// --- MinHeap ---

// Zamiana miejscami elementów kopca i aktualizacja ich pozycji
void Dijkstra::MinHeap::swap(int i, int j) {
    int temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
    pos[heap[i]] = i;
    pos[heap[j]] = j;
}

// "Przesiewanie" w dół w kopcu w celu zachowania własności kopca
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

// "Przesiewanie" w górę w kopcu po zmianie wartości klucza
void Dijkstra::MinHeap::heapifyUp(int i) {
    int parent = (i - 1) / 2;
    if (i && dist[heap[i]] < dist[heap[parent]]) {
        swap(i, parent);
        heapifyUp(parent);
    }
}

// Konstruktor kopca - alokacja tablic heap i pos
Dijkstra::MinHeap::MinHeap(int cap, int* d) : capacity(cap), dist(d), size(0) {
    heap = new int[capacity];
    pos = new int[capacity];
    for (int i = 0; i < capacity; i++)
        pos[i] = -1;
}

// Destruktor kopca - zwalnianie pamięci
Dijkstra::MinHeap::~MinHeap() {
    delete[] heap;
    delete[] pos;
}

// Wstawienie nowego wierzchołka do kopca
void Dijkstra::MinHeap::insert(int v) {
    heap[size] = v;
    pos[v] = size;
    size++;
    heapifyUp(size - 1);
}

// Sprawdzenie czy kopiec jest pusty
bool Dijkstra::MinHeap::empty() const {
    return size == 0;
}

// Pobranie elementu z minimalnym dystansem z kopca
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

// Zmniejszenie klucza w kopcu (pozycja wierzchołka)
void Dijkstra::MinHeap::decreaseKey(int v) {
    int i = pos[v];
    heapifyUp(i);
}

// Sprawdzenie czy wierzchołek jest w kopcu
bool Dijkstra::MinHeap::contains(int v) const {
    return pos[v] != -1;
}

// --- Dijkstra ---

// Destruktor zwalniający pamięć zaalokowaną na wyniki
Dijkstra::~Dijkstra() {
    if (distances) {
        delete[] distances;
        distances = nullptr;
    }
    if (previous) {
        delete[] previous;
        previous = nullptr;
    }
}

// Główna funkcja algorytmu Dijkstry
void Dijkstra::run(Graph* graph, int startVertex, int endVertex) {
    start = startVertex;
    end = endVertex;
    vertexCount = graph->getVertexCount();

    int* dist = new int[vertexCount];
    int* prev = new int[vertexCount];

    // Inicjalizacja tablic odległości i poprzedników
    for (int i = 0; i < vertexCount; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }

    dist[start] = 0; // Odległość do startu = 0
    MinHeap minHeap(vertexCount, dist);
    for (int i = 0; i < vertexCount; i++)
        minHeap.insert(i);

    // Pętla główna algorytmu
    while (!minHeap.empty()) {
        int u = minHeap.extractMin();
        if (u == -1 || dist[u] == INT_MAX) break;

        // Przeglądaj sąsiadów wierzchołka u
        int neighborCount = graph->getNeighborCount(u);
        for (int i = 0; i < neighborCount; i++) {
            int v = graph->getNeighbor(u, i);
            int weight = graph->getEdgeWeight(u, v);

            // Relaksacja krawędzi
            if (weight > 0 && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                if (minHeap.contains(v))
                    minHeap.decreaseKey(v); // Aktualizacja pozycji w kopcu
            }
        }
    }

    // Zapisanie wyników do statycznych pól klasy
    if (distances) delete[] distances;
    if (previous) delete[] previous;
    distances = dist;
    previous = prev;
}

// Wyświetlanie najkrótszej ścieżki i jej kosztu
void Dijkstra::displayResult() const {
    std::cout << "Shortest path from " << start << " to " << end << ": ";
    if (!distances || distances[end] == INT_MAX) {
        std::cout << "NO PATH\n";
        return;
    }

    std::cout << distances[end] << "\nPath: ";

    int* path = new int[vertexCount];
    int temp = end, length = 0;

    // Rekonstrukcja ścieżki wstecz po tablicy previous
    while (temp != -1) {
        path[length++] = temp;
        temp = previous[temp];
    }

    // Wyświetlenie ścieżki od startu do celu
    for (int i = length - 1; i >= 0; i--) {
        std::cout << path[i];
        if (i > 0) std::cout << " -> ";
    }
    std::cout << "\n";

    delete[] path;
}
