#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"

class Dijkstra {
public:
    void run(Graph* graph, int src, int dest);
    void displayResult() const;
};

#endif // DIJKSTRA_H
