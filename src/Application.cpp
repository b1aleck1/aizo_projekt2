#include "../include/Application.h"
#include "../include/Timer.h"
#include <iostream>
#include <fstream>
#include <string> // Dodano dla std::string

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
    // Ścieżka do config.txt jest teraz względna względem katalogu roboczego (projekt2/)
    // Jeśli katalog roboczy to 'projekt2/', to './data/config.txt' odnosi się do 'projekt2/data/config.txt'
    if (!config.loadConfigFromFile("./data/config.txt")) {
        std::cerr << "Error loading configuration file. Using default values.\n";
        // Możesz dodać exit(-1); tutaj, jeśli brak konfiguracji jest krytyczny
    }

    // --- Sekcja debugowania konfiguracji ---
    std::cout << "\n=== Configuration Loaded ===\n";
    std::cout << "[DEBUG] Problem Type: " << (config.getProblemType() == MST ? "MST" : "SP") << "\n";
    std::cout << "[DEBUG] Graph File: '" << config.getInputFile() << "'\n";
    std::cout << "[DEBUG] Vertices (if random): " << config.getVertexCount() << "\n";
    std::cout << "[DEBUG] Density (if random): " << config.getDensity() << "\n";
    std::cout << "[DEBUG] Use Matrix: " << (config.isUseMatrixRepresentation() ? "true" : "false") << "\n";
    std::cout << "[DEBUG] Use List: " << (config.isUseListRepresentation() ? "true" : "false") << "\n";
    std::cout << "[DEBUG] Display Graph: " << (config.isShowGraph() ? "true" : "false") << "\n";
    std::cout << "[DEBUG] Run Performance Tests: " << (config.isRunPerformanceTests() ? "true" : "false") << "\n";
    if (config.getProblemType() == SP) {
        std::cout << "[DEBUG] Source Vertex: " << config.getSourceVertex() << "\n";
        std::cout << "[DEBUG] Destination Vertex: " << config.getDestinationVertex() << "\n";
    }
    std::cout << "==========================\n\n";
    // --- Koniec sekcji debugowania konfiguracji ---


    if (!config.getInputFile().empty()) {
        std::cout << "[INFO] Graph file specified. Attempting to load graph.\n";
        if (!loadGraphFromFile(config.getInputFile())) {
            std::cerr << "Failed to load graph from file. Please check the file path, existence, and format.\n";
            return; // Zakończ program, jeśli nie można wczytać grafu
        }
    } else {
        std::cout << "[INFO] No graph file specified in config. Generating a random graph.\n";
        generateGraph();
    }

    if (config.isShowGraph()) {
        displayGraphs();
    }

    runAlgorithms();

    if (config.isRunPerformanceTests()) {
        std::cout << "\n=== Performance Tests ===\n";
        // Tutaj będzie implementacja testów wydajnościowych.

    }
}

bool Application::loadGraphFromFile(const std::string& filename) {
    // Debug: Pełna ścieżka do pliku, którą program próbuje otworzyć
    std::cout << "[DEBUG] Attempting to open graph file: '" << filename << "'\n";

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[ERROR] Could not open graph file: '" << filename << "'. Verify file path, permissions, and existence.\n";
        return false;
    }
    std::cout << "[DEBUG] Graph file successfully opened.\n";

    int numEdges, numVertices;
    // Sprawdzenie, czy odczyt pierwszych wartości się powiódł
    if (!(file >> numEdges >> numVertices)) {
        std::cerr << "[ERROR] Failed to read number of edges and vertices from '" << filename << "'. File might be empty, corrupted, or in wrong format.\n";
        file.close();
        return false;
    }
    std::cout << "[DEBUG] Read " << numVertices << " vertices and " << numEdges << " edges from file.\n";

    // Inicjalizacja grafów na podstawie wczytanych rozmiarów
    if (config.isUseMatrixRepresentation()) {
        delete matrixGraph; // Upewnij się, że poprzedni graf jest usunięty
        matrixGraph = new MatrixGraph(numVertices, config.getProblemType() == SP);
    }
    if (config.isUseListRepresentation()) {
        delete listGraph; // Upewnij się, że poprzedni graf jest usunięty
        listGraph = new ListGraph(numVertices, config.getProblemType() == SP);
    }

    for (int i = 0; i < numEdges; ++i) {
        int src, dest, weight;
        // Sprawdzenie, czy odczyt krawędzi się powiódł
        if (!(file >> src >> dest >> weight)) {
            std::cerr << "[ERROR] Failed to read edge " << i + 1 << " from '" << filename << "'. File might be incomplete or corrupted.\n";
            file.close();
            return false;
        }
        if (matrixGraph) matrixGraph->addEdge(src, dest, weight);
        if (listGraph) listGraph->addEdge(src, dest, weight);
    }
    std::cout << "[DEBUG] Successfully loaded all " << numEdges << " edges from file.\n";

    file.close();
    return true;
}

void Application::generateGraph() {
    int v = config.getVertexCount();
    double d = config.getDensity();
    std::cout << "[INFO] Generating random graph with " << v << " vertices and density " << d << ".\n";

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
    std::cout << "[DEBUG] Random graph generation complete.\n";
}

void Application::displayGraphs() {
    std::cout << "\n=== Graph Display ===\n";
    if (matrixGraph) {
        std::cout << "\n--- Matrix Representation ---\n";
        matrixGraph->display();
    }
    if (listGraph) {
        std::cout << "\n--- List Representation ---\n";
        listGraph->display();
    }
    std::cout << "=======================\n";
}

void Application::runAlgorithms() {
    if (config.getProblemType() == MST) {
        std::cout << "\n=== Running MST Algorithms ===\n";
        if (config.isRunPrim()) {
            std::cout << "\n--- Prim's Algorithm ---\n";
            if (matrixGraph) {
                std::cout << "Matrix: " << runPrimMST(matrixGraph) << " ms\n";
            }
            if (listGraph) {
                std::cout << "List: " << runPrimMST(listGraph) << " ms\n";
            }
        } else {
            std::cout << "[INFO] Prim's Algorithm not enabled in config.\n";
        }

        if (config.isRunKruskal()) {
            std::cout << "\n--- Kruskal's Algorithm ---\n";
            if (matrixGraph) {
                std::cout << "Matrix: " << runKruskalMST(matrixGraph) << " ms\n";
            }
            if (listGraph) {
                std::cout << "List: " << runKruskalMST(listGraph) << " ms\n";
            }
        } else {
            std::cout << "[INFO] Kruskal's Algorithm not enabled in config.\n";
        }
    } else if (config.getProblemType() == SP) {
        int src = config.getSourceVertex();
        int dest = config.getDestinationVertex();
        std::cout << "\n=== Running Shortest Path Algorithms (Source: " << src << ", Destination: " << dest << ") ===\n";

        if (config.isRunDijkstra()) {
            std::cout << "\n--- Dijkstra's Algorithm ---\n";
            if (matrixGraph) {
                std::cout << "Matrix: " << runDijkstraSP(matrixGraph, src, dest) << " ms\n";
            }
            if (listGraph) {
                std::cout << "List: " << runDijkstraSP(listGraph, src, dest) << " ms\n";
            }
        } else {
            std::cout << "[INFO] Dijkstra's Algorithm not enabled in config.\n";
        }

        if (config.isRunBellmanFord()) {
            std::cout << "\n--- Bellman-Ford Algorithm ---\n";
            if (matrixGraph) {
                std::cout << "Matrix: " << runBellmanFordSP(matrixGraph, src, dest) << " ms\n";
            }
            if (listGraph) {
                std::cout << "List: " << runBellmanFordSP(listGraph, src, dest) << " ms\n";
            }
        } else {
            std::cout << "[INFO] Bellman-Ford Algorithm not enabled in config.\n";
        }
    }
}