#include "../include/Application.h"
#include "../include/Config.h"
#include "../include/Graph.h"
#include "../include/ListGraph.h"
#include "../include/MatrixGraph.h"
#include "../include/Timer.h"
#include <iostream>
#include <fstream>
#include <string>

// External function declarations
double runPrimMST(Graph* graph);
double runKruskalMST(Graph* graph);
double runDijkstraSP(Graph* graph, int src, int dest);
double runBellmanFordSP(Graph* graph, int src, int dest);
void generateConnectedGraph(Graph* graph, int vertices, double density);

// Function to load graph from file
bool loadGraphFromFile(const std::string& filename, Graph* matrixGraph, Graph* listGraph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    // Read first line: number of edges and vertices
    int numEdges, numVertices;
    file >> numEdges >> numVertices;

    // Recreate graphs with proper size
    if (matrixGraph) {
        delete matrixGraph;
        matrixGraph = new MatrixGraph(numVertices, false);
    }

    if (listGraph) {
        delete listGraph;
        listGraph = new ListGraph(numVertices, false);
    }

    // Read edges
    for (int i = 0; i < numEdges; i++) {
        int src, dest, weight;
        file >> src >> dest >> weight;

        // Add edge to both representations
        if (matrixGraph) {
            matrixGraph->addEdge(src, dest, weight);
        }

        if (listGraph) {
            listGraph->addEdge(src, dest, weight);
        }
    }

    file.close();
    return true;
}

int main() {
    // Load configuration
    Config config;
    if (!config.loadConfigFromFile("config.txt")) {
        std::cerr << "Error loading configuration file. Using default values.\n";
    }

    // Create graphs based on selected representations
    MatrixGraph* matrixGraph = nullptr;
    ListGraph* listGraph = nullptr;

    // Initialize graphs based on config
    if (config.isUseMatrixRepresentation()) {
        matrixGraph = new MatrixGraph(config.getVertexCount(), config.getProblemType() == SP);
    }

    if (config.isUseListRepresentation()) {
        listGraph = new ListGraph(config.getVertexCount(), config.getProblemType() == SP);
    }

    // Load graph from file or generate random graph
    if (!config.getInputFile().empty()) {
        if (!loadGraphFromFile(config.getInputFile(), matrixGraph, listGraph)) {
            std::cerr << "Failed to load graph from file. Exiting.\n";
            return 1;
        }
    } else {
        // Generate random graph
        if (matrixGraph) {
            generateConnectedGraph(matrixGraph, config.getVertexCount(), config.getDensity());
        }

        if (listGraph) {
            generateConnectedGraph(listGraph, config.getVertexCount(), config.getDensity());
        }
    }

    // Display graphs if requested
    if (config.isShowGraph()) {
        if (matrixGraph) {
            std::cout << "Matrix Representation:\n";
            matrixGraph->display();
        }

        if (listGraph) {
            std::cout << "List Representation:\n";
            listGraph->display();
        }
    }

    // Run selected algorithm(s)
    if (config.getProblemType() == MST) {
        // Run MST algorithms
        if (config.isRunPrim()) {
            std::cout << "\n=== Prim's Algorithm ===\n";

            if (matrixGraph) {
                std::cout << "Matrix Representation:\n";
                double time = runPrimMST(matrixGraph);
                std::cout << "Execution Time: " << time << " ms\n";
            }

            if (listGraph) {
                std::cout << "List Representation:\n";
                double time = runPrimMST(listGraph);
                std::cout << "Execution Time: " << time << " ms\n";
            }
        }

        if (config.isRunKruskal()) {
            std::cout << "\n=== Kruskal's Algorithm ===\n";

            if (matrixGraph) {
                std::cout << "Matrix Representation:\n";
                double time = runKruskalMST(matrixGraph);
                std::cout << "Execution Time: " << time << " ms\n";
            }

            if (listGraph) {
                std::cout << "List Representation:\n";
                double time = runKruskalMST(listGraph);
                std::cout << "Execution Time: " << time << " ms\n";
            }
        }
    } else if (config.getProblemType() == SP) {
        // Run Shortest Path algorithms
        int src = config.getSourceVertex();
        int dest = config.getDestinationVertex();

        if (config.isRunDijkstra()) {
            std::cout << "\n=== Dijkstra's Algorithm ===\n";

            if (matrixGraph) {
                std::cout << "Matrix Representation:\n";
                double time = runDijkstraSP(matrixGraph, src, dest);
                std::cout << "Execution Time: " << time << " ms\n";
            }

            if (listGraph) {
                std::cout << "List Representation:\n";
                double time = runDijkstraSP(listGraph, src, dest);
                std::cout << "Execution Time: " << time << " ms\n";
            }
        }

        if (config.isRunBellmanFord()) {
            std::cout << "\n=== Bellman-Ford Algorithm ===\n";

            if (matrixGraph) {
                std::cout << "Matrix Representation:\n";
                double time = runBellmanFordSP(matrixGraph, src, dest);
                std::cout << "Execution Time: " << time << " ms\n";
            }

            if (listGraph) {
                std::cout << "List Representation:\n";
                double time = runBellmanFordSP(listGraph, src, dest);
                std::cout << "Execution Time: " << time << " ms\n";
            }
        }
    }

    // Run performance tests if requested
    if (config.isRunPerformanceTests()) {
        // Implementation for performance tests
        std::cout << "\n=== Performance Tests ===\n";
        // Create performance test code here for different vertex counts and densities
    }

    // Cleanup
    if (matrixGraph) delete matrixGraph;
    if (listGraph) delete listGraph;

    return 0;
}
