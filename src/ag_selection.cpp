#include "../include/ag_selection.h"

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
                                        int nr_vertices, int graph_degree,
                                        const std::vector<std::list<int>>& adjacency_list) {

    // Evaluate P
    // Try to combine the fitness of the coloring and the conflicts
    // std::vector<int> pop_values = calculate_conflict_fitness(pop, adjacency_list);
    // std::vector<int> pop_values = calculate_coloring_fitness(pop);
    std::vector<int> pop_values = calculate_col_fit_with_penalizing(pop, adjacency_list);

    // Tune Selection Pressure
    /*scale_values(pop_values, 1.0, 2.0);
    raise_to_power(pop_values, 4);*/

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

    // Selection, the elite pop will be 0
    std::vector<std::vector<int>> new_population;
    for (size_t i = 0; i < pop_size / 2 - elite_pool; ++i) {
        int index = select_index(accumulated_probability_vector);
        new_population.push_back(pop[index]);
    }
    // Insert newly generated chromosomes into the new population
    std::vector<std::vector<int>> new_chromosomes = generate_population(pop_size / 2, nr_vertices, graph_degree);

    new_population.insert(new_population.end(), new_chromosomes.begin(), new_chromosomes.end());

    // Add the elite chromosomes to the new population
    new_population.insert(new_population.end(), elite_population.begin(), elite_population.end());

    return new_population;
}