#include "../include/genetic_operators.h"

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

    std::vector<int> pop_values = calculate_conflict_fitness(population, adjacency_list);

    std::vector<std::size_t> sorted_indices(population.size());
    std::iota(sorted_indices.begin(), sorted_indices.end(), 0);
    std::sort(sorted_indices.begin(), sorted_indices.end(), [&pop_values](std::size_t i, std::size_t j) {
        return pop_values[i] < pop_values[j];
    });

    for (std::size_t i = 0; i + 1 < sorted_indices.size(); i += 2) {
        // Select two parents for crossover
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


void corrective_mutation(std::vector<std::vector<int>>& population, const int& graph_degree,
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

void random_mutation(std::vector<std::vector<int>>& population, const int& graph_degree,
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

std::vector<std::vector<int>> elitism(const std::vector<std::vector<int>>& population,
                                      const std::vector<int>& population_values,
                                      size_t elite_pool) {

    std::vector<size_t> indices(population.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::sort(indices.begin(), indices.end(),
              [&population_values](size_t a, size_t b) {
                  return population_values[a] < population_values[b];
              });

    std::vector<std::vector<int>> elite_population;
    for (size_t i = 0; i < elite_pool; ++i) {
        elite_population.push_back(population[indices[i]]);
    }

    return elite_population;
}

std::vector<std::vector<int>> selection(const std::vector<std::vector<int>>& pop,int pop_size, int elite_pool,
                                         const std::vector<std::list<int>>& adjacency_list) {

    // Evaluate P
    std::vector<int> pop_values = calculate_conflict_fitness(pop, adjacency_list);

    // Tune Selection Pressure
    /*scale_values(pop_values, 1.0, 2.0);
    raise_to_power(pop_values, 1);*/

    // Perform elitism and get the k best chromosomes
    std::vector<std::vector<int>> elite_population = elitism(pop, pop_values, elite_pool);

    // Total fitness
    double values_sum = std::accumulate(pop_values.begin(), pop_values.end(), 0.0);

    // Individual probability
    std::vector<double> probability_vector;
    for (const auto& i : pop_values) {
        probability_vector.push_back((1.0 / i) / values_sum);
    }

    // Normalize probabilities
    double probability_sum = std::accumulate(probability_vector.begin(), probability_vector.end(), 0.0);
    for (auto& probability : probability_vector) {
        probability /= probability_sum;
    }

    // Accumulated probability
    std::vector<double> accumulated_probability_vector;
    std::partial_sum(probability_vector.begin(), probability_vector.end(), std::back_inserter(accumulated_probability_vector));
    accumulated_probability_vector.back() = 1.00;

    // Selection
    std::vector<std::vector<int>> new_population;
    for (size_t i = 0; i < pop_size - elite_pool; ++i) {
        int index = select_index(accumulated_probability_vector);
        new_population.push_back(pop[index]);
    }

    // Add the elite chromosomes to the new population
    new_population.insert(new_population.end(), elite_population.begin(), elite_population.end());

    return new_population;
}