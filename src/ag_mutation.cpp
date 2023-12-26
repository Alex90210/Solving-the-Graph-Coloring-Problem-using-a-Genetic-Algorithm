#include "../include/ag_mutation.h"

void corrective_mutation_on_every_conflict(std::vector<std::vector<int>>& population, const int& graph_degree,
                                           const std::vector<std::list<int>>& adjacency_list, const int& vertices_nr) {

    static std::vector<int> all_colors = create_color_vector(graph_degree);
    for (auto& chromosome : population) {
        for (size_t i = 0; i < vertices_nr; ++i) {
            if (has_same_color_neighbor(i, chromosome, adjacency_list)) {
                std::vector<int> adjacent_colors = get_adjacent_colors(i, chromosome, adjacency_list);
                std::vector<int> valid_colors = find_non_adjacent_colors(all_colors, adjacent_colors);

                if (!valid_colors.empty()) {
                    int new_color = valid_colors[get_random_int(0, valid_colors.size() - 1)];
                    chromosome[i] = new_color;
                }
            }
        }
    }
}

void corrective_mutation_randomly(std::vector<std::vector<int>>& population, const int& graph_degree,
                                  const double& mutation_probability,
                                  const std::vector<std::list<int>>& adjacency_list, const int& vertices_nr) {

    static std::vector<int> all_colors = create_color_vector(graph_degree);
    for (auto& chromosome : population) {
        for (size_t i = 0; i < vertices_nr; ++i) {
            // Random chance of mutation
            if (get_random_double(0, 1) < mutation_probability) {
                if (has_same_color_neighbor(i, chromosome, adjacency_list)) {
                    std::vector<int> adjacent_colors = get_adjacent_colors(i, chromosome, adjacency_list);
                    std::vector<int> valid_colors = find_non_adjacent_colors(all_colors, adjacent_colors);

                    if (!valid_colors.empty()) {
                        int new_color = valid_colors[get_random_int(0, valid_colors.size() - 1)];
                        chromosome[i] = new_color;
                    }
                }
            }
        }
    }
}

void random_mutation_on_every_conflict(std::vector<std::vector<int>>& population, const int& graph_degree,
                                       const std::vector<std::list<int>>& adjacency_list, const int& vertices_nr) {

    static std::vector<int> all_colors = create_color_vector(graph_degree);
    for (auto& chromosome : population) {
        for (size_t i = 0; i < vertices_nr; ++i) {
            if (has_same_color_neighbor(i, chromosome, adjacency_list)) {
                int new_color = all_colors[get_random_int(0, all_colors.size() - 1)];
                chromosome[i] = new_color;
            }
        }
    }
}