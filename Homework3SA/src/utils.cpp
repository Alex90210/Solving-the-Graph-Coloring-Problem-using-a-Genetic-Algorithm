#include "../include/utils.h"

void read_col_file(const std::string& filename, std::vector<std::list<int>>& adjacency_list) {
    std::ifstream file(filename);
    std::string line;
    int numVertices = 0, numEdges = 0;

    if (file.is_open()) {
        while (getline(file, line)) {
            if (line[0] == 'p') {
                std::istringstream iss(line);
                std::string temp;
                iss >> temp >> temp >> numVertices >> numEdges;
                adjacency_list.resize(numVertices);
            } else if (line[0] == 'e') {
                std::istringstream iss(line);
                std::string temp;
                int v1, v2;
                iss >> temp >> v1 >> v2;
                if (std::find(adjacency_list[v1 - 1].begin(), adjacency_list[v1 - 1].end(), v2 - 1) == adjacency_list[v1 - 1].end()) {
                    adjacency_list[v1 - 1].push_back(v2 - 1);
                    adjacency_list[v2 - 1].push_back(v1 - 1);
                }
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file";
    }
}

int get_random_int(int min, int max) {
    static std::random_device rd;
    static std::mt19937 eng(rd());

    std::uniform_int_distribution<int> distribution(min, max);

    return distribution(eng);
}

int find_max_degree(const std::vector<std::list<int>>& adjacencyList) {
    int max_degree = 0;
    for (const auto& edges : adjacencyList) {
        max_degree = std::max(max_degree, static_cast<int>(edges.size()));
    }
    return max_degree;
}

double get_random_double(double min, double max) {
    static bool initialized = false;

    if (!initialized) {
        std::srand(static_cast<unsigned>(std::time(0)));
        initialized = true;
    }

    double random_normalized = static_cast<double>(std::rand()) / RAND_MAX;
    return min + random_normalized * (max - min);
}