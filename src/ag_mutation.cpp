#include "../include/ag_mutation.h"

void corrective_mutation_on_every_conflict(std::vector<std::vector<int>>& population, const int& graph_degree,
                                           const std::vector<std::list<int>>& adjacency_list, const int& vertices_nr,
                                           double mutation_probability, int best_colorization) {

    for (auto& chromosome : population) {
        std::vector<int> all_colors(chromosome.begin(), chromosome.end());
        std::sort(all_colors.begin(), all_colors.end());
        all_colors.erase(std::unique(all_colors.begin(), all_colors.end()), all_colors.end());
        if (get_random_double(0, 1) <= mutation_probability) {
            for (size_t i = 0; i < chromosome.size(); ++i) {
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

void corrective_mutation_randomly(std::vector<std::vector<int>>& population, const int& graph_degree,
                                  const double& mutation_probability,
                                  const std::vector<std::list<int>>& adjacency_list, const int& vertices_nr) {

    static std::vector<int> all_colors = create_color_vector(graph_degree);
    for (auto& chromosome : population) {
        for (size_t i = 0; i < graph_degree; ++i) {
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

    for (auto& chromosome : population) {
        // Construct all_colors from the current chromosome
        std::vector<int> all_colors(chromosome.begin(), chromosome.end());
        std::sort(all_colors.begin(), all_colors.end());
        all_colors.erase(std::unique(all_colors.begin(), all_colors.end()), all_colors.end());

        for (size_t i = 0; i < vertices_nr; ++i) {
            if (has_same_color_neighbor(i, chromosome, adjacency_list)) {
                int new_color = all_colors[get_random_int(0, all_colors.size() - 1)];
                chromosome[i] = new_color;
            }
        }
    }
}

void random_mutation(std::vector<std::vector<int>>& population, const int& graph_degree,
                     const double& mutation_probability) {

    for (auto& chromosome : population) {
        // Construct valid_colors in the range [0, graph_degree - 1]
        std::vector<int> valid_colors;
        for (int color = 0; color < graph_degree; ++color) {
            valid_colors.push_back(color);
        }

        // Random chance of mutation
        for (size_t i = 0; i < chromosome.size(); ++i) {
            if (get_random_double(0, 1) < mutation_probability) {
                int new_color = valid_colors[get_random_int(0, valid_colors.size() - 1)];
                chromosome[i] = new_color;
            }
        }
    }
}


void corrective_mutation_population(std::vector<std::vector<int>>& population,
                                    const std::vector<std::list<int>>& adjacency_list,
                                    const int& max_color,
                                    const double& mutation_probability) {
    for (auto& chromosome : population) {
        // Apply mutation based on the probability
        if (get_random_double(0.0, 1.0) < mutation_probability) {
            for (size_t vertex = 0; vertex < chromosome.size(); ++vertex) {
                std::set<int> used_colors;

                // Get colors used by adjacent vertices
                for (const int& neighbor : adjacency_list[vertex]) {
                    used_colors.insert(chromosome[neighbor]);
                }

                // Find the smallest color not used by neighbors
                for (int color = 1; color <= max_color; ++color) {
                    if (used_colors.find(color) == used_colors.end()) {
                        chromosome[vertex] = color;
                        break;
                    }
                }
            }
        }
    }
}

bool has_conflict(const std::vector<int>& chromosome, const std::vector<std::list<int>>& adjacency_list) {
    for (size_t vertex = 0; vertex < chromosome.size(); ++vertex) {
        for (const int& neighbor : adjacency_list[vertex]) {
            if (chromosome[vertex] == chromosome[neighbor]) {
                return true;
            }
        }
    }
    return false;
}

void corrective_mutation_until_valid(std::vector<std::vector<int>>& population,
                                     const std::vector<std::list<int>>& adjacency_list,
                                     const int& max_color,
                                     const int max_iterations) { // Set a limit to iterations
    for (auto& chromosome : population) {
        int iterations = 0;
        while (has_conflict(chromosome, adjacency_list) && iterations < max_iterations) {
            for (size_t vertex = 0; vertex < chromosome.size(); ++vertex) {
                std::set<int> used_colors;

                // Get colors used by adjacent vertices
                for (const int& neighbor : adjacency_list[vertex]) {
                    used_colors.insert(chromosome[neighbor]);
                }

                // Find the smallest color not used by neighbors
                for (int color = 1; color <= max_color; ++color) {
                    if (used_colors.find(color) == used_colors.end()) {
                        chromosome[vertex] = color;
                        break;
                    }
                }
            }
            iterations++;
        }

        // Optional: Handle the case where a valid solution couldn't be found
        if (iterations >= max_iterations) {
            // Handle accordingly, e.g., log a message or flag the chromosome
        }
    }
}

bool greedy_improvement(const std::vector<std::vector<int>>& population, const std::vector<std::list<int>>& adjacency_list) {
    std::vector<int> evaluated = calculate_col_fit_with_penalizing(population, adjacency_list, 10);
    auto iter = std::min_element(evaluated.begin(), evaluated.end());
    int best_fitness = *iter;
    int index = std::distance(evaluated.begin(), iter);
    std::vector<int> best_chromosome = population[index];

    bool improved = false;
    for(size_t vertex = 0; vertex < best_chromosome.size(); ++vertex) {
        std::vector<int> adjacent_colors = get_adjacent_colors(vertex, best_chromosome, adjacency_list);
        std::vector<int> valid_colors = find_non_adjacent_colors(create_color_vector(10), adjacent_colors);
        for (int color : valid_colors) {
            std::vector<int> neighbour = best_chromosome;
            neighbour[vertex] = color;
            int neighbour_fitness = calculate_col_fit_with_penalizing_chr(neighbour, adjacency_list);
            if (neighbour_fitness < best_fitness) {
                best_chromosome = neighbour;
                best_fitness = neighbour_fitness;
                improved = true;
            }
        }
    }

    return improved;
}