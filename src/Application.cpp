#include "../include/Application.h"
#include "../include/Timer.h"
#include <iostream>
#include <fstream>

// External algorithm implementations
extern double runPrimMST(Graph* graph);
extern double runKruskalMST(Graph* graph);
extern double runDijkstraSP(Graph* graph, int src, int dest);
extern double runBellmanFordSP(Graph* graph, int src, int dest);
extern void generateConnectedGraph(Graph* graph, int vertices, double density);

Application::Application()
    : matrixGraph(nullptr), listGraph(nullptr) {}

Application::~Application() {
    delete matrixGraph;
    delete listGraph;
}

void Application::run() {
    if (!config.loadConfigFromFile("../data/config.txt")) {
        std::cerr << "Error loading configuration file. Using default values.\n";
    }

    if (!config.getInputFile().empty()) {
        if (!loadGraphFromFile(config.getInputFile())) {
            std::cerr << "Failed to load graph from file.\n";
            return;
        }
    } else {
        generateGraph();
    }

    if (config.isShowGraph()) {
        displayGraphs();
    }

    runAlgorithms();

    if (config.isRunPerformanceTests()) {
        std::cout << "\n=== Performance Tests ===\n";
        // Add performance test implementation here
    }
}

bool Application::loadGraphFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    int numEdges, numVertices;
    file >> numEdges >> numVertices;

    if (config.isUseMatrixRepresentation()) {
        delete matrixGraph;
        matrixGraph = new MatrixGraph(numVertices, config.getProblemType() == SP);
    }
    if (config.isUseListRepresentation()) {
        delete listGraph;
        listGraph = new ListGraph(numVertices, config.getProblemType() == SP);
    }

    for (int i = 0; i < numEdges; ++i) {
        int src, dest, weight;
        file >> src >> dest >> weight;
        if (matrixGraph) matrixGraph->addEdge(src, dest, weight);
        if (listGraph) listGraph->addEdge(src, dest, weight);
    }

    file.close();
    return true;
}

void Application::generateGraph() {
    int v = config.getVertexCount();
    double d = config.getDensity();

    if (config.isUseMatrixRepresentation()) {
        delete matrixGraph;
        matrixGraph = new MatrixGraph(v, config.getProblemType() == SP);
        generateConnectedGraph(matrixGraph, v, d);
    }

    if (config.isUseListRepresentation()) {
        delete listGraph;
        listGraph = new ListGraph(v, config.getProblemType() == SP);
        generateConnectedGraph(listGraph, v, d);
    }
}

void Application::displayGraphs() {
    if (matrixGraph) {
        std::cout << "Matrix Representation:\n";
        matrixGraph->display();
    }
    if (listGraph) {
        std::cout << "List Representation:\n";
        listGraph->display();
    }
}

void Application::runAlgorithms() {
    if (config.getProblemType() == MST) {
        if (config.isRunPrim()) {
            std::cout << "\n=== Prim's Algorithm ===\n";
            if (matrixGraph) {
                std::cout << "Matrix:\n";
                std::cout << "Time: " << runPrimMST(matrixGraph) << " ms\n";
            }
            if (listGraph) {
                std::cout << "List:\n";
                std::cout << "Time: " << runPrimMST(listGraph) << " ms\n";
            }
        }

        if (config.isRunKruskal()) {
            std::cout << "\n=== Kruskal's Algorithm ===\n";
            if (matrixGraph) {
                std::cout << "Matrix:\n";
                std::cout << "Time: " << runKruskalMST(matrixGraph) << " ms\n";
            }
            if (listGraph) {
                std::cout << "List:\n";
                std::cout << "Time: " << runKruskalMST(listGraph) << " ms\n";
            }
        }
    } else if (config.getProblemType() == SP) {
        int src = config.getSourceVertex();
        int dest = config.getDestinationVertex();

        if (config.isRunDijkstra()) {
            std::cout << "\n=== Dijkstra's Algorithm ===\n";
            if (matrixGraph) {
                std::cout << "Matrix:\n";
                std::cout << "Time: " << runDijkstraSP(matrixGraph, src, dest) << " ms\n";
            }
            if (listGraph) {
                std::cout << "List:\n";
                std::cout << "Time: " << runDijkstraSP(listGraph, src, dest) << " ms\n";
            }
        }

        if (config.isRunBellmanFord()) {
            std::cout << "\n=== Bellman-Ford Algorithm ===\n";
            if (matrixGraph) {
                std::cout << "Matrix:\n";
                std::cout << "Time: " << runBellmanFordSP(matrixGraph, src, dest) << " ms\n";
            }
            if (listGraph) {
                std::cout << "List:\n";
                std::cout << "Time: " << runBellmanFordSP(listGraph, src, dest) << " ms\n";
            }
        }
    }
}
