#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include "Graph.h"

class BellmanFord {
public:
    void run(Graph* graph, int src, int dest);
    void displayResult() const;

private:
    static int* distances;
    static int* previous;
    static int vertexCount;
    static int start;
    static int end;
};

#endif // BELLMANFORD_H
