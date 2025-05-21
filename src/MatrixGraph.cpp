#include "../include/MatrixGraph.h"
#include <iostream>

MatrixGraph::MatrixGraph(int vertices, bool isDirected)
    : Graph(vertices, isDirected)
{
    adjMatrix = new int*[vertices];
    for (int i = 0; i < vertices; ++i) {
        adjMatrix[i] = new int[vertices];
        for (int j = 0; j < vertices; ++j)
            adjMatrix[i][j] = 0;
    }
}

MatrixGraph::~MatrixGraph() {
    clearGraph();
    for (int i = 0; i < vertexCount; ++i)
        delete[] adjMatrix[i];
    delete[] adjMatrix;
}

bool MatrixGraph::addEdge(int src, int dest, int weight) {
    if (src < 0 || src >= vertexCount || dest < 0 || dest >= vertexCount) return false;
    adjMatrix[src][dest] = weight;
    if (!directed) adjMatrix[dest][src] = weight;
    edgeCount++;
    return true;
}

bool MatrixGraph::removeEdge(int src, int dest) {
    if (src < 0 || src >= vertexCount || dest < 0 || dest >= vertexCount) return false;
    adjMatrix[src][dest] = 0;
    if (!directed) adjMatrix[dest][src] = 0;
    edgeCount--;
    return true;
}

bool MatrixGraph::hasEdge(int src, int dest) const {
    if (src < 0 || src >= vertexCount || dest < 0 || dest >= vertexCount) return false;
    return adjMatrix[src][dest] != 0;
}

int MatrixGraph::getEdgeWeight(int src, int dest) const {
    if (src < 0 || src >= vertexCount || dest < 0 || dest >= vertexCount) return 0;
    return adjMatrix[src][dest];
}

void MatrixGraph::display() const {
    for (int i = 0; i < vertexCount; ++i) {
        for (int j = 0; j < vertexCount; ++j)
            std::cout << adjMatrix[i][j] << " ";
        std::cout << std::endl;
    }
}

void MatrixGraph::clearGraph() {
    for (int i = 0; i < vertexCount; ++i)
        for (int j = 0; j < vertexCount; ++j)
            adjMatrix[i][j] = 0;
    edgeCount = 0;
}
