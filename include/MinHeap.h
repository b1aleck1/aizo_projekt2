#ifndef MINHEAP_H
#define MINHEAP_H

struct VertexDistance {
    int vertex;
    int distance;

    VertexDistance(int v, int d);
};

class MinHeap {
private:
    VertexDistance** heap;
    int* position;
    int heapSize;
    int capacity;

    void swap(int a, int b);
    void minHeapify(int idx);

public:
    MinHeap(int capacity);
    ~MinHeap();

    bool isEmpty() const;
    void insert(int vertex, int distance);
    VertexDistance* extractMin();
    void decreaseKey(int vertex, int newDistance);
    bool isInHeap(int vertex) const;
};

#endif // MINHEAP_H
