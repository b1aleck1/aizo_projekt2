#include "../include/ListGraph.h"
#include <iostream>

ListGraph::ListGraph(int vertices, bool isDirected)
    : Graph(vertices, isDirected)
{
    adjList = new Node*[vertices];
    for (int i = 0; i < vertices; ++i)
        adjList[i] = nullptr;
}

ListGraph::~ListGraph() {
    clearGraph();
    delete[] adjList;
}

bool ListGraph::addEdge(int src, int dest, int weight) {
    if (src < 0 || src >= vertexCount || dest < 0 || dest >= vertexCount) return false;
    Node* newNode = new Node(dest, weight);
    newNode->next = adjList[src];
    adjList[src] = newNode;
    if (!directed) {
        Node* newNode2 = new Node(src, weight);
        newNode2->next = adjList[dest];
        adjList[dest] = newNode2;
    }
    edgeCount++;
    return true;
}

bool ListGraph::removeEdge(int src, int dest) {
    if (src < 0 || src >= vertexCount || dest < 0 || dest >= vertexCount) return false;
    Node* prev = nullptr;
    Node* curr = adjList[src];
    while (curr) {
        if (curr->vertex == dest) {
            if (prev) prev->next = curr->next;
            else adjList[src] = curr->next;
            delete curr;
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    if (!directed) {
        prev = nullptr;
        curr = adjList[dest];
        while (curr) {
            if (curr->vertex == src) {
                if (prev) prev->next = curr->next;
                else adjList[dest] = curr->next;
                delete curr;
                break;
            }
            prev = curr;
            curr = curr->next;
        }
    }
    edgeCount--;
    return true;
}

bool ListGraph::hasEdge(int src, int dest) const {
    if (src < 0 || src >= vertexCount || dest < 0 || dest >= vertexCount) return false;
    Node* curr = adjList[src];
    while (curr) {
        if (curr->vertex == dest) return true;
        curr = curr->next;
    }
    return false;
}

int ListGraph::getEdgeWeight(int src, int dest) const {
    if (src < 0 || src >= vertexCount || dest < 0 || dest >= vertexCount) return 0;
    Node* curr = adjList[src];
    while (curr) {
        if (curr->vertex == dest) return curr->weight;
        curr = curr->next;
    }
    return 0;
}

void ListGraph::display() const {
    for (int i = 0; i < vertexCount; ++i) {
        std::cout << i << ": ";
        Node* curr = adjList[i];
        while (curr) {
            std::cout << "(" << curr->vertex << ", " << curr->weight << ") ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }
}

int ListGraph::getNeighborCount(int vertex) const {
    int count = 0;
    Node* current = adjList[vertex];
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

int ListGraph::getNeighbor(int vertex, int index) const {
    int count = 0;
    Node* current = adjList[vertex];
    while (current) {
        if (count == index) return current->vertex;
        count++;
        current = current->next;
    }
    return -1; // Nie znaleziono
}


void ListGraph::clearGraph() {
    for (int i = 0; i < vertexCount; ++i) {
        Node* curr = adjList[i];
        while (curr) {
            Node* toDelete = curr;
            curr = curr->next;
            delete toDelete;
        }
        adjList[i] = nullptr;
    }
    edgeCount = 0;
}
