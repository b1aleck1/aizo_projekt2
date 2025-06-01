#include "../include/MatrixGraph.h"
#include <iostream>
#include <iomanip>
#include <string>

MatrixGraph::MatrixGraph(int vertices, bool isDirected)
    : Graph(vertices, isDirected)
{
    maxEdges = vertices * (vertices - 1);
    incMatrix = new int*[vertexCount];
    for (int i = 0; i < vertexCount; ++i) {
        incMatrix[i] = new int[maxEdges];
        for (int j = 0; j < maxEdges; ++j)
            incMatrix[i][j] = 0;
    }
    edges = new IncidenceEdge[maxEdges];
    edgeCount = 0;
}

MatrixGraph::~MatrixGraph() {
    clearGraph();
    for (int i = 0; i < vertexCount; ++i)
        delete[] incMatrix[i];
    delete[] incMatrix;
    delete[] edges;
}

bool MatrixGraph::addEdge(int src, int dest, int weight) {
    if (src < 0 || src >= vertexCount || dest < 0 || dest >= vertexCount) {
        std::cerr << "[MatrixGraph ERROR] Invalid vertex index in addEdge: src=" << src << ", dest=" << dest << "\n";
        return false;
    }
    if (edgeCount >= maxEdges) {
        std::cerr << "[MatrixGraph ERROR] Cannot add edge: maximum number of edges reached.\n";
        return false;
    }

    for (int e = 0; e < edgeCount; ++e) {
        if (directed) {
            if (edges[e].from == src && edges[e].to == dest) {
                if (edges[e].weight == weight) return false;
            }
        } else {
            if ((edges[e].from == src && edges[e].to == dest) ||
                (edges[e].from == dest && edges[e].to == src)) {
                if (edges[e].weight == weight) return false;
            }
        }
    }

    edges[edgeCount].from = src;
    edges[edgeCount].to = dest;
    edges[edgeCount].weight = weight;

    for (int v_idx = 0; v_idx < vertexCount; ++v_idx) {
        incMatrix[v_idx][edgeCount] = 0;
    }

    if (directed) {
        incMatrix[src][edgeCount] = -weight;
        incMatrix[dest][edgeCount] = weight;
    } else {
        // TUTAJ BYŁ BŁĄD! Powinno być "weight", a nie "1"
        incMatrix[src][edgeCount] = weight;
        incMatrix[dest][edgeCount] = weight;
    }

    edgeCount++;
    return true;
}

bool MatrixGraph::removeEdge(int src, int dest) {
    for (int e = 0; e < edgeCount; ++e) {
        bool match = (edges[e].from == src && edges[e].to == dest);
        if (!directed && edges[e].from == dest && edges[e].to == src) {
            match = true;
        }

        if (match) {
            for (int j = e; j < edgeCount - 1; ++j) {
                edges[j] = edges[j + 1];
            }

            for (int v = 0; v < vertexCount; ++v) {
                for (int j = e; j < edgeCount - 1; ++j) {
                    incMatrix[v][j] = incMatrix[v][j + 1];
                }
                incMatrix[v][edgeCount - 1] = 0;
            }
            edgeCount--;
            return true;
        }
    }
    return false;
}

bool MatrixGraph::hasEdge(int src, int dest) const {
    for (int e = 0; e < edgeCount; ++e) {
        if (directed) {
            if (edges[e].from == src && edges[e].to == dest) {
                return true;
            }
        } else {
            if ((edges[e].from == src && edges[e].to == dest) ||
                (edges[e].from == dest && edges[e].to == src)) {
                return true;
            }
        }
    }
    return false;
}

int MatrixGraph::getEdgeWeight(int src, int dest) const {
    for (int e = 0; e < edgeCount; ++e) {
        if (directed) {
            if (edges[e].from == src && edges[e].to == dest) {
                return edges[e].weight;
            }
        } else {
            if ((edges[e].from == src && edges[e].to == dest) ||
                (edges[e].from == dest && edges[e].to == src)) {
                return edges[e].weight;
            }
        }
    }
    return 0;
}


void MatrixGraph::display() const {
    std::cout << "Incidence matrix (" << vertexCount << " vertices, " << edgeCount << " edges):\n";

    for (int i = 0; i < vertexCount; ++i) {
        std::cout << std::setw(2) << i << " | ";
        for (int j = 0; j < edgeCount; ++j) {
            if (directed) {
                if (incMatrix[i][j] < 0) {
                    std::cout << std::setw(4) << std::to_string(incMatrix[i][j]) << " ";
                } else if (incMatrix[i][j] > 0) {
                    std::cout << std::setw(4) << incMatrix[i][j] << " ";
                } else {
                    std::cout << std::setw(4) << 0 << " ";
                }
            } else { // Graf nieskierowany
                if (incMatrix[i][j] != 0) { // Jeśli jest incydentne, wypisz wagę (nie 0)
                    std::cout << std::setw(4) << incMatrix[i][j] << " ";
                } else {
                    std::cout << std::setw(4) << 0 << " ";
                }
            }
        }
        std::cout << "\n";
    }

    std::cout << "\nEdges:\n";
    for (int e = 0; e < edgeCount; ++e) {
        std::cout << "E" << e << ": " << edges[e].from << " -> " << edges[e].to << " (weight: " << edges[e].weight << ")\n";
    }
}

int MatrixGraph::getNeighborCount(int vertex) const {
    int count = 0;
    for (int e = 0; e < edgeCount; ++e) {
        if (directed) {
            if (edges[e].from == vertex) count++;
        } else {
            if (edges[e].from == vertex || edges[e].to == vertex) count++;
        }
    }
    return count;
}

int MatrixGraph::getNeighbor(int vertex, int index) const {
    int count = 0;
    for (int e = 0; e < edgeCount; ++e) {
        if (directed) {
            if (edges[e].from == vertex) {
                if (count == index) return edges[e].to;
                count++;
            }
        } else {
            if (edges[e].from == vertex) {
                if (count == index) return edges[e].to;
                count++;
            } else if (edges[e].to == vertex) {
                if (count == index) return edges[e].from;
                count++;
            }
        }
    }
    return -1; // Nie znaleziono
}


void MatrixGraph::clearGraph() {
    for (int i = 0; i < vertexCount; ++i) {
        for (int j = 0; j < maxEdges; ++j) {
            incMatrix[i][j] = 0;
        }
    }
    edgeCount = 0;
}