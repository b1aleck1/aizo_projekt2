#ifndef GRAPH_H
#define GRAPH_H

class Graph {
protected:
    int vertexCount;
    int edgeCount;
    bool directed;

public:
    Graph(int vertices, bool isDirected = false);
    virtual ~Graph();

    virtual bool addEdge(int source, int destination, int weight) = 0;
    virtual bool removeEdge(int source, int destination) = 0;
    virtual bool hasEdge(int source, int destination) const = 0;
    virtual int getEdgeWeight(int source, int destination) const = 0;
    virtual void display() const = 0;

    int getVertexCount() const { return vertexCount; }
    int getEdgeCount() const { return edgeCount; }
    bool isDirected() const { return directed; }

    virtual void clearGraph() = 0;
};

#endif // GRAPH_H
