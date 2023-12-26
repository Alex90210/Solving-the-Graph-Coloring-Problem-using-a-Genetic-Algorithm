#include "../include/col_operators.h"

void read_col_file(const std::string& filename, std::vector<std::list<int>>& adjacencyList) {
    std::ifstream file(filename);
    std::string line;
    int numVertices = 0, numEdges = 0;

    if (file.is_open()) {
        while (getline(file, line)) {
            if (line[0] == 'p') {
                std::istringstream iss(line);
                std::string temp;
                iss >> temp >> temp >> numVertices >> numEdges;
                adjacencyList.resize(numVertices);
            } else if (line[0] == 'e') {
                std::istringstream iss(line);
                std::string temp;
                int v1, v2;
                iss >> temp >> v1 >> v2;
                if (std::find(adjacencyList[v1 - 1].begin(), adjacencyList[v1 - 1].end(), v2 - 1) == adjacencyList[v1 - 1].end()) {
                    adjacencyList[v1 - 1].push_back(v2 - 1);
                    adjacencyList[v2 - 1].push_back(v1 - 1);
                }
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file";
    }
}

int find_max_degree(const std::vector<std::list<int>>& adjacencyList) {
    int max_degree = 0;
    for (const auto& edges : adjacencyList) {
        max_degree = std::max(max_degree, static_cast<int>(edges.size()));
    }
    return max_degree;
}

int count_vertices(const std::vector<std::list<int>>& adjacencyList) {
    return adjacencyList.size();
}

bool has_same_color_neighbor(int vertex, const std::vector<int>& colors, const std::vector<std::list<int>>& adjacencyList) {
    int vertex_color = colors[vertex];
    for (auto neighbor : adjacencyList[vertex]) {
        if (colors[neighbor] == vertex_color) {
            return true;
        }
    }
    return false;
}

std::vector<int> get_adjacent_colors(int vertex, const std::vector<int>& chromosome,
                                     const std::vector<std::list<int>>& adjacency_list) {

    std::vector<int> adjacent_colors;
    for (int neighbor : adjacency_list[vertex]) {
        adjacent_colors.push_back(chromosome[neighbor]);
    }
    return adjacent_colors;
}

std::vector<int> create_color_vector(int graph_degree) {
    std::vector<int> colors;
    for (int i = 0; i <= graph_degree; ++i) {
        colors.push_back(i);
    }
    return colors;
}

std::vector<int> find_non_adjacent_colors(const std::vector<int>& all_colors, const std::vector<int>& adjacent_colors) {
    std::vector<int> sorted_all_colors = all_colors;
    std::sort(sorted_all_colors.begin(), sorted_all_colors.end());

    std::vector<int> sorted_adjacent_colors = adjacent_colors;
    std::sort(sorted_adjacent_colors.begin(), sorted_adjacent_colors.end());

    std::vector<int> non_adjacent_colors;
    std::set_difference(sorted_all_colors.begin(), sorted_all_colors.end(),
                        sorted_adjacent_colors.begin(), sorted_adjacent_colors.end(),
                        std::back_inserter(non_adjacent_colors));

    return non_adjacent_colors;
}

int get_coloring_number(const std::vector<int>& chromosome) {
    std::unordered_set<int> unique_colors(chromosome.begin(), chromosome.end());
    return unique_colors.size();
}