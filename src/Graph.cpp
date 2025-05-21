#include "../include/Graph.h"

Graph::Graph(int vertices, bool isDirected)
    : vertexCount(vertices), edgeCount(0), directed(isDirected) {
}

Graph::~Graph() {
    // Virtual destructor
}
