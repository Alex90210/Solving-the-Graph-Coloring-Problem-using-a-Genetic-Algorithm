#include "../include/ag_crossover.h"

void simple_crossover(std::vector<std::vector<int>>& population) {
    // This has 100% cx prob.
    for (size_t i{ 0 }; i < population.size() - 1; ++i) {
        for (size_t j{ i + 1 }; j < population.size(); ++j) {
            unsigned chromosome_cut_point = get_random_int(0, population[i].size() - 1);
            for (size_t k = chromosome_cut_point; k < population[i].size(); ++k)
                std::swap(population[i][k], population[j][k]);
        }
    }
}

void crossover(std::vector<std::vector<int>>& population, const double& crossover_probability) {

    for (size_t i{ 0 }; i < population.size() - 1; ++i) {
        if (get_random_double(0, 1) <= crossover_probability) {
            for (size_t j{ i + 1 }; j < population.size(); ++j) {
                if (get_random_double(0, 1) <= crossover_probability) {
                    unsigned chromosome_cut_point = get_random_int(0, population[i].size() - 1);
                    for (size_t k = chromosome_cut_point; k < population[i].size(); ++k)
                        std::swap(population[i][k], population[j][k]);
                    i = j;
                    continue;
                }
            }
        }
    }
}

void crossover_by_fitness(std::vector<std::vector<int>>& population, const double& crossover_probability,
                          const std::vector<std::list<int>>& adjacency_list) {

    // std::vector<int> pop_values = calculate_conflict_fitness(population, adjacency_list);
    std::vector<int> pop_values = calculate_col_fit_with_penalizing(population, adjacency_list, 22);

    std::vector<std::size_t> sorted_indices(population.size());
    std::iota(sorted_indices.begin(), sorted_indices.end(), 0);
    std::sort(sorted_indices.begin(), sorted_indices.end(), [&pop_values](std::size_t i, std::size_t j) {
        return pop_values[i] < pop_values[j];
    });

    for (std::size_t i = 0; i + 1 < sorted_indices.size(); i += 2) {
        std::vector<int>& parent1 = population[sorted_indices[i]];
        std::vector<int>& parent2 = population[sorted_indices[i + 1]];

        if (get_random_double(0, 1) <= crossover_probability) {
            std::size_t crossover_point = get_random_int(0, parent1.size() - 1);

            for (std::size_t k = crossover_point; k < parent1.size(); ++k)
                std::swap(parent1[k], parent2[k]);
        }
    }
}

void crossover_random_shuffle(std::vector<std::vector<int>>& population, const double& crossover_probability) {
    static std::random_device rd;
    static std::mt19937 g(rd());

    std::shuffle(population.begin(), population.end(), g);

    for (size_t i = 0; i < population.size() - 1; i += 2) {
        if (get_random_double(0, 1) <= crossover_probability) {
            unsigned chromosome_cut_point = get_random_int(0, population[i].size() - 1);
            for (size_t k = chromosome_cut_point; k < population[i].size(); ++k) {
                std::swap(population[i][k], population[i + 1][k]);
            }
        }
    }
}