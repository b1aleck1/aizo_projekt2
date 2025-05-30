#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"

class Dijkstra {
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

#endif // DIJKSTRA_H
