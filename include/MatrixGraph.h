#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H

#include "Graph.h"

struct IncidenceEdge {
    int from;
    int to;
    int weight;
};

class MatrixGraph : public Graph {
private:
    int** incMatrix;         // [vertexCount][edgeCount]
    IncidenceEdge* edges;    // tablica krawędzi (from, to, weight)
    int maxEdges;            // maksymalna liczba krawędzi (dla alokacji)

public:
    MatrixGraph(int vertices, bool isDirected = false);
    ~MatrixGraph();

    bool addEdge(int source, int destination, int weight) override;
    bool removeEdge(int source, int destination) override;
    bool hasEdge(int source, int destination) const override;
    int getEdgeWeight(int source, int destination) const override;
    void display() const override;
    void clearGraph() override;
    int getNeighborCount(int vertex) const override;
    int getNeighbor(int vertex, int index) const override;

};

#endif // MATRIX_GRAPH_H
