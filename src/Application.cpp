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
    int choice;
    do {
        displayMenu();
        std::cin >> choice;
        processMenuChoice(choice);
    } while (choice != 0);
}

void Application::displayMenu() {
    std::cout << "\nGraph Algorithms Implementation\n";
    std::cout << "==============================\n";
    std::cout << "1. Load graph from file\n";
    std::cout << "2. Generate random graph\n";
    std::cout << "3. Display graph (matrix representation)\n";
    std::cout << "4. Display graph (list representation)\n";
    std::cout << "5. Run Prim's algorithm\n";
    std::cout << "6. Run Kruskal's algorithm\n";
    std::cout << "7. Run Dijkstra's algorithm\n";
    std::cout << "8. Run Bellman-Ford algorithm\n";
    std::cout << "9. Run performance tests\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}

// Implement other methods: processMenuChoice, loadGraphFromFile, generateRandomGraph,
// runMSTPrim, runMSTKruskal, runSPDijkstra, runSPBellmanFord, performanceTest
