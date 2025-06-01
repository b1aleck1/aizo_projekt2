#include "../include/MinHeap.h"

VertexDistance::VertexDistance(int v, int d) : vertex(v), distance(d) {}

MinHeap::MinHeap(int capacity) : capacity(capacity), heapSize(0) {
    heap = new VertexDistance*[capacity];
    position = new int[capacity];
    for (int i = 0; i < capacity; i++) {
        position[i] = -1; // Inicjalnie wszystkie wierzchołki są poza kopcem
    }
}

MinHeap::~MinHeap() {
    for (int i = 0; i < heapSize; i++) {
        delete heap[i]; // Zwolnienie pamięci zaalokowanej dla elementów kopca
    }
    delete[] heap;
    delete[] position;
}

bool MinHeap::isEmpty() const {
    return heapSize == 0;
}

void MinHeap::swap(int a, int b) {
    VertexDistance* temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;

    // Aktualizacja pozycji wierzchołków po zamianie
    position[heap[a]->vertex] = a;
    position[heap[b]->vertex] = b;
}

void MinHeap::minHeapify(int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;  // Indeks lewego dziecka
    int right = 2 * idx + 2; // Indeks prawego dziecka

    // Znajdź najmniejszy z trzech: rodzica, lewego i prawego dziecka
    if (left < heapSize && heap[left]->distance < heap[smallest]->distance) {
        smallest = left;
    }
    if (right < heapSize && heap[right]->distance < heap[smallest]->distance) {
        smallest = right;
    }

    // Jeśli najmniejszy nie jest bieżącym elementem, przesuń w dół
    if (smallest != idx) {
        swap(idx, smallest);
        minHeapify(smallest);
    }
}

VertexDistance* MinHeap::extractMin() {
    if (isEmpty()) return nullptr;

    VertexDistance* root = heap[0];                // Najmniejszy element (korzeń)
    VertexDistance* lastNode = heap[heapSize - 1]; // Ostatni element w kopcu
    heap[0] = lastNode;                            // Przenieś ostatni element na początek

    position[root->vertex] = -1;                   // Usuń korzeń z pozycji
    position[lastNode->vertex] = 0;                // Zaktualizuj pozycję nowego korzenia

    heapSize--;
    minHeapify(0);                                 // Przywróć strukturę kopca

    return root;                                   // Zwróć najmniejszy element
}

void MinHeap::decreaseKey(int vertex, int newDistance) {
    int idx = position[vertex];
    heap[idx]->distance = newDistance;

    // Przesuwanie w górę kopca, jeśli nowy dystans jest mniejszy niż u rodzica
    while (idx > 0 && heap[idx]->distance < heap[(idx - 1) / 2]->distance) {
        swap(idx, (idx - 1) / 2);
        idx = (idx - 1) / 2;
    }
}

bool MinHeap::isInHeap(int vertex) const {
    return position[vertex] != -1; // Wierzchołek znajduje się w kopcu, jeśli jego pozycja jest różna od -1
}

void MinHeap::insert(int vertex, int distance) {
    VertexDistance* newNode = new VertexDistance(vertex, distance);
    heap[heapSize] = newNode;
    position[vertex] = heapSize;

    int i = heapSize;
    heapSize++;

    // Przesuwanie nowego elementu w górę, aby utrzymać właściwości kopca
    while (i > 0 && heap[i]->distance < heap[(i - 1) / 2]->distance) {
        swap(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}
