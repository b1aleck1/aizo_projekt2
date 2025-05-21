#ifndef LIST_GRAPH_H
#define LIST_GRAPH_H

#include "Graph.h"

// Node structure for adjacency list
struct Node {
    int vertex;
    int weight;
    Node* next;

    Node(int v, int w) : vertex(v), weight(w), next(nullptr) {}
};

class ListGraph : public Graph {
private:
    Node** adjList; // Array of linked lists

public:
    ListGraph(int vertices, bool isDirected = false);
    ~ListGraph();

    bool addEdge(int source, int destination, int weight) override;
    bool removeEdge(int source, int destination) override;
    bool hasEdge(int source, int destination) const override;
    int getEdgeWeight(int source, int destination) const override;
    void display() const override;
    void clearGraph() override;
};

#endif // LIST_GRAPH_H
