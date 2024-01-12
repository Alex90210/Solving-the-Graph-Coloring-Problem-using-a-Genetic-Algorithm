#include "../include/col_operators.h"
#include "../include/GA.h"

int main() {
    std::vector<std::list<int>> adjacencyList;
    std::string filename = "../test_instances/queen7_7.col";

    read_col_file(filename, adjacencyList);

    int vertexNumber = 0;
    for (const auto& neighbors : adjacencyList) {
        std::cout << "Vertex " << vertexNumber << ": ";
        for (int neighbor : neighbors) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
        vertexNumber++;
    }

    int maxDegree = find_max_degree(adjacencyList);
    std::cout << "The maximum degree of the graph is: " << maxDegree << std::endl;

    const int pop_size {50};
    const int elite_pool {25};
    const double mut_p {0};
    const double cx_prob {1.0};
    const double corrective_mut_p {0.25};
    const int vertices_nr = count_vertices(adjacencyList);
    const int graph_degree = find_max_degree(adjacencyList);
    const int generations {4000};
    const int runs {10};

    std::vector<double> times;
    double bestTime = std::numeric_limits<double>::max();
    double worstTime = 0.0;
    int bestSolution = std::numeric_limits<int>::max();
    int worstSolution = 0;

    for (int run = 0; run < runs; ++run) {
        auto start = std::chrono::high_resolution_clock::now();

        int solution = genetic_algorithm(pop_size, elite_pool, vertices_nr, graph_degree, generations, mut_p, cx_prob, adjacencyList);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        double currentTime = duration.count();
        times.push_back(currentTime);

        if (currentTime < bestTime) {
            bestTime = currentTime;
            bestSolution = solution;
        }
        if (currentTime > worstTime) {
            worstTime = currentTime;
            worstSolution = solution;
        }

        std::cout << "Run " << (run + 1) << ": Solution: " << solution << " (Time: " << currentTime << "s)" << std::endl;
    }

    double averageTime = std::accumulate(times.begin(), times.end(), 0.0) / times.size();

    std::cout << "\nAverage Time: " << averageTime << "s\n";
    std::cout << "Best Solution: " << bestSolution << " (Time: " << bestTime << "s)\n";
    std::cout << "Worst Solution: " << worstSolution << " (Time: " << worstTime << "s)\n";

    return 0;
}
