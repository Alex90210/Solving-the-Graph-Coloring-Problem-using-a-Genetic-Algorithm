#include "../include/GA.h"

int genetic_algorithm(int pop_size, int elite_pool, int vertices_nr, int graph_degree, int max_gen,
                      const double& cx_prob, const std::vector<std::list<int>>& adjacency_list) {

    std::vector<std::vector<int>> pop = generate_population(pop_size, vertices_nr, graph_degree);
    std::vector<int> pop_values_as_conflicts = calculate_conflict_fitness(pop, adjacency_list);
    auto min_iter = std::min_element(pop_values_as_conflicts.begin(), pop_values_as_conflicts.end());
    int min_conflict = *min_iter;

    int current_generation {0};
    int best_color_nr {graph_degree};
    while (current_generation < max_gen) {

        current_generation++;
        // SELECTION
        selection(pop, pop_size, elite_pool, adjacency_list);



        // MUTATION
        if (min_conflict >= 4) // this works better alone
            corrective_mutation(pop, graph_degree, adjacency_list, vertices_nr);
        else
            random_mutation(pop, graph_degree, adjacency_list, vertices_nr);


        // CROSSOVER
        simple_crossover(pop);
        // crossover(pop, cx_prob);
        // crossover_by_fitness(pop, cx_prob, adjacency_list);
        // crossover_random_shuffle(pop, cx_prob);


        // EVALUATION
        pop_values_as_conflicts = calculate_conflict_fitness(pop, adjacency_list);
        std::vector<int> pop_values_as_colors = calculate_coloring_fitness(pop);

        int new_best_color_sol{graph_degree + 1};
        for (size_t i{0}; i < pop_values_as_colors.size(); ++i)
            if (pop_values_as_colors[i] < new_best_color_sol && pop_values_as_conflicts[i] == 0) {
                new_best_color_sol = pop_values_as_colors[i];
            }

        if (new_best_color_sol < best_color_nr) {
            best_color_nr = new_best_color_sol;
        }
    }

    return best_color_nr;
}