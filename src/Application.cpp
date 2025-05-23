#include "../include/Application.h"
#include <iostream>

Application::Application()
    : matrixGraph(nullptr), listGraph(nullptr) {
}

Application::~Application() {
    if (matrixGraph) delete matrixGraph;
    if (listGraph) delete listGraph;
}

void Application::run() {
    // 1. Wczytaj konfigurację
    if (!config.loadConfigFromFile("config.txt")) {
        std::cerr << "Error loading configuration file. Using default values.\n";
    }

    int vertices = config.getVertexCount();

    // 2. Utwórz grafy
    if (config.isUseMatrixRepresentation()) {
        matrixGraph = new MatrixGraph(vertices, config.getProblemType() == SP);
    }
    if (config.isUseListRepresentation()) {
        listGraph = new ListGraph(vertices, config.getProblemType() == SP);
    }

    // 3. Wczytaj graf z pliku lub wygeneruj losowy
    if (!config.getInputFile().empty()) {
        if (!loadGraphFromFile(config.getInputFile().c_str())) {
            std::cerr << "Failed to load graph from file. Exiting.\n";
            return;
        }
    } else {
        if (!generateRandomGraph(vertices, config.getDensity())) {
            std::cerr << "Failed to generate random graph. Exiting.\n";
            return;
        }
    }

    // 4. Wyświetl graf, jeśli wymaga konfiguracja
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

    // 5. Uruchom algorytmy na podstawie konfiguracji
    if (config.getProblemType() == MST) {
        if (config.isRunPrim()) {
            std::cout << "\n=== Prim's Algorithm ===\n";
            if (matrixGraph) {
                std::cout << "Matrix Representation:\n";
                runMSTPrim(matrixGraph);
            }
            if (listGraph) {
                std::cout << "List Representation:\n";
                runMSTPrim(listGraph);
            }
        }

        if (config.isRunKruskal()) {
            std::cout << "\n=== Kruskal's Algorithm ===\n";
            if (matrixGraph) {
                std::cout << "Matrix Representation:\n";
                runMSTKruskal(matrixGraph);
            }
            if (listGraph) {
                std::cout << "List Representation:\n";
                runMSTKruskal(listGraph);
            }
        }
    } else if (config.getProblemType() == SP) {
        int src = config.getSourceVertex();
        int dest = config.getDestinationVertex();

        if (config.isRunDijkstra()) {
            std::cout << "\n=== Dijkstra's Algorithm ===\n";
            if (matrixGraph) {
                std::cout << "Matrix Representation:\n";
                runSPDijkstra(matrixGraph, src, dest);
            }
            if (listGraph) {
                std::cout << "List Representation:\n";
                runSPDijkstra(listGraph, src, dest);
            }
        }

        if (config.isRunBellmanFord()) {
            std::cout << "\n=== Bellman-Ford Algorithm ===\n";
            if (matrixGraph) {
                std::cout << "Matrix Representation:\n";
                runSPBellmanFord(matrixGraph, src, dest);
            }
            if (listGraph) {
                std::cout << "List Representation:\n";
                runSPBellmanFord(listGraph, src, dest);
            }
        }
    }

    // 6. Testy wydajności, jeśli wymagane
    if (config.isRunPerformanceTests()) {
        std::cout << "\n=== Performance Tests ===\n";
        runPerformanceTests();
    }
}

// Przykładowe implementacje metod do wczytywania i generowania grafu

bool Application::loadGraphFromFile(const char* filename) {
    // Implementacja analogiczna do tej z main.cpp — wczytaj do matrixGraph i listGraph
    // ...
    return true;
}

bool Application::generateRandomGraph(int vertices, double density) {
    // Implementacja analogiczna do generateConnectedGraph — dla matrixGraph i listGraph
    // ...
    return true;
}

void Application::runMSTPrim(Graph* graph) {
    double time = runPrimMST(graph);
    std::cout << "Execution Time: " << time << " ms\n";
}

void Application::runMSTKruskal(Graph* graph) {
    double time = runKruskalMST(graph);
    std::cout << "Execution Time: " << time << " ms\n";
}

void Application::runSPDijkstra(Graph* graph, int source, int destination) {
    double time = runDijkstraSP(graph, source, destination);
    std::cout << "Execution Time: " << time << " ms\n";
}

void Application::runSPBellmanFord(Graph* graph, int source, int destination) {
    double time = runBellmanFordSP(graph, source, destination);
    std::cout << "Execution Time: " << time << " ms\n";
}

void Application::runPerformanceTests() {
    // Tutaj implementacja testów wydajnościowych
}
