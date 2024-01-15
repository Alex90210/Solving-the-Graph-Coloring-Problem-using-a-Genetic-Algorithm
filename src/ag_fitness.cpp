#include "../include/ag_fitness.h"

std::vector<int> calculate_conflict_fitness(const std::vector<std::vector<int>>& population,
                                            const std::vector<std::list<int>>& adjacency_list) {

    std::vector<int> pop_values;

    for (auto& chromosome: population) {
        int fitness = 0;
        for (size_t i = 0; i < chromosome.size(); ++i) {
            int vertex_color = chromosome[i];
            for (int neighbor: adjacency_list[i]) {
                if (vertex_color == chromosome[neighbor]) {
                    fitness++;
                }
            }
        }
        pop_values.push_back(fitness / 2);
    }

    return pop_values;
}

std::vector<int> calculate_coloring_fitness(const std::vector<std::vector<int>>& population) {
    std::vector<int> population_coloring_numbers;
    population_coloring_numbers.reserve(population.size());

    for (const auto& chromosome : population) {
        int coloring_number = get_coloring_number(chromosome);
        population_coloring_numbers.push_back(coloring_number);
    }

    return population_coloring_numbers;
}

std::vector<int> calculate_col_fit_with_penalizing(const std::vector<std::vector<int>>& population,
                                                   const std::vector<std::list<int>>& adjacency_list,
                                                   const int& best_colorization) {
    std::vector<int> population_fitness;
    population_fitness.reserve(population.size());

    int max_degree = find_max_degree(adjacency_list);

    for (const auto& chromosome : population) {
        int fitness = get_coloring_number(chromosome);
        // int fitness = {0};
        std::set<std::pair<int, int>> counted_conflicts;

        for (size_t i = 0; i < chromosome.size(); ++i) {
            int vertex_color = chromosome[i];
            for (int neighbor : adjacency_list[i]) {
                if (vertex_color == chromosome[neighbor]) {
                    if (counted_conflicts.insert(std::minmax(i, static_cast<size_t>(neighbor))).second) {
                        fitness += max_degree;
                    }
                }
            }
        }

        population_fitness.push_back(fitness);
    }

    return population_fitness;
}

int calculate_col_fit_with_penalizing_chr(const std::vector<int>& chromosome, const std::vector<std::list<int>>& adjacency_list) {
    int chr_fitness;
    int max_degree = find_max_degree(adjacency_list);

    int fitness = get_coloring_number(chromosome);

    std::set<std::pair<int, int>> counted_conflicts;

    for (size_t i = 0; i < chromosome.size(); ++i) {
        int vertex_color = chromosome[i];
        for (int neighbor : adjacency_list[i]) {
            if (vertex_color == chromosome[neighbor]) {
                if (counted_conflicts.insert(std::minmax(i, static_cast<size_t>(neighbor))).second) {
                    fitness += max_degree;
                }
            }
        }
    }

    return fitness;
}