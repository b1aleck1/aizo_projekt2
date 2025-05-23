#include "../include/MinHeap.h"

VertexDistance::VertexDistance(int v, int d) : vertex(v), distance(d) {}

MinHeap::MinHeap(int capacity) : capacity(capacity), heapSize(0) {
    heap = new VertexDistance*[capacity];
    position = new int[capacity];
    for (int i = 0; i < capacity; i++) {
        position[i] = -1;
    }
}

MinHeap::~MinHeap() {
    for (int i = 0; i < heapSize; i++) {
        delete heap[i];
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

    position[heap[a]->vertex] = a;
    position[heap[b]->vertex] = b;
}

void MinHeap::minHeapify(int idx) {
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

VertexDistance* MinHeap::extractMin() {
    if (isEmpty()) return nullptr;

    VertexDistance* root = heap[0];
    VertexDistance* lastNode = heap[heapSize - 1];
    heap[0] = lastNode;

    position[root->vertex] = -1;
    position[lastNode->vertex] = 0;

    heapSize--;
    minHeapify(0);

    return root;
}

void MinHeap::decreaseKey(int vertex, int newDistance) {
    int idx = position[vertex];
    heap[idx]->distance = newDistance;

    while (idx > 0 && heap[idx]->distance < heap[(idx - 1) / 2]->distance) {
        swap(idx, (idx - 1) / 2);
        idx = (idx - 1) / 2;
    }
}

bool MinHeap::isInHeap(int vertex) const {
    return position[vertex] != -1;
}

void MinHeap::insert(int vertex, int distance) {
    VertexDistance* newNode = new VertexDistance(vertex, distance);
    heap[heapSize] = newNode;
    position[vertex] = heapSize;

    int i = heapSize;
    heapSize++;

    while (i > 0 && heap[i]->distance < heap[(i - 1) / 2]->distance) {
        swap(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}
