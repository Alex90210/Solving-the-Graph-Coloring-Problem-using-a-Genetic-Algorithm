#include "../include/GA.h"

int genetic_algorithm(int pop_size, int elite_pool, int vertices_nr, int graph_degree, int max_gen, double mut_p,
                      const double& cx_prob, const std::vector<std::list<int>>& adjacency_list) {

    std::vector<std::vector<int>> pop = generate_population(pop_size, vertices_nr, graph_degree, graph_degree);

    int best_colorization {graph_degree + 1};
    int new_best_colorization {graph_degree + 2};

    std::vector<int> pop_values_conflicts = calculate_conflict_fitness(pop, adjacency_list);
    auto iter = std::min_element(pop_values_conflicts.begin(), pop_values_conflicts.end());
    int min_conflict = *iter;
    std::vector<int> pop_values_conflicts_and_penalizing = calculate_col_fit_with_penalizing(pop, adjacency_list, best_colorization);

    int current_generation {0};
    int generations_without_improvement {0};

    while (current_generation < max_gen) {

        current_generation++;
        pop = selection(pop, pop_size, elite_pool, vertices_nr, graph_degree, adjacency_list, best_colorization);

        if (generations_without_improvement > 50) {
            if (!greedy_improvement(pop, adjacency_list)) {
                random_mutation(pop, graph_degree, 0.3);
                crossover_random_shuffle(pop, cx_prob);
                generations_without_improvement = 0;
            }
            else {
                crossover_random_shuffle(pop, cx_prob);
            }
        }
        /*else if (min_conflict < 4) {
            corrective_mutation_randomly(pop, graph_degree, mut_p, adjacency_list, vertices_nr);
            crossover_by_fitness(pop, cx_prob, adjacency_list);
        }*/
        else {
            corrective_mutation_on_every_conflict(pop, graph_degree, adjacency_list, vertices_nr, mut_p, best_colorization);
           // crossover_by_fitness(pop, cx_prob, adjacency_list);
            crossover_random_shuffle(pop, cx_prob);
        }

        // corrective_mutation_on_every_conflict(pop, graph_degree, adjacency_list, vertices_nr, mut_p, best_colorization);
        // random_mutation(pop, graph_degree, mut_p);
        // crossover_random_shuffle(pop, cx_prob);
        // simple_crossover(pop);
        // crossover_by_fitness(pop, cx_prob, adjacency_list);

        pop_values_conflicts_and_penalizing = calculate_col_fit_with_penalizing(pop, adjacency_list, best_colorization);
        pop_values_conflicts = calculate_conflict_fitness(pop, adjacency_list);
        std::vector<int> pop_values_colors = calculate_coloring_fitness(pop);

        for (size_t i{0}; i < pop_values_conflicts_and_penalizing.size(); ++i) {
            if (pop_values_colors[i] < new_best_colorization && pop_values_conflicts_and_penalizing[i] < graph_degree) {
                new_best_colorization = pop_values_colors[i];
            }
        }

        if (new_best_colorization < best_colorization) {
            best_colorization = new_best_colorization;
            // At this point the colours should be consolidated ( 2 4 13 - > 1 2 3 ). And sorted?
            generations_without_improvement = 0;
        }
        else {
            generations_without_improvement++;
        }
    }

    return best_colorization;
}