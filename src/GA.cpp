#include "../include/GA.h"

int genetic_algorithm(int pop_size, int elite_pool, int vertices_nr, int graph_degree, int max_gen, double mut_p,
                      const double& cx_prob, const std::vector<std::list<int>>& adjacency_list) {

    std::vector<std::vector<int>> pop = generate_population(pop_size, vertices_nr, graph_degree);

    std::vector<int> pop_values = calculate_col_fit_with_penalizing(pop, adjacency_list);
    // std::vector<int> pop_values = calculate_conflict_fitness(pop, adjacency_list);

    /*auto min_iter = std::min_element(pop_values_as_conflicts.begin(), pop_values_as_conflicts.end());
    int min_conflict = *min_iter;*/

    int current_generation {0};
    int generations_without_improvement {0};

    int best_color_nr {graph_degree};
    int new_best_color_sol {graph_degree + 1};

    while (current_generation < max_gen) {

        current_generation++;
        selection(pop, pop_size, elite_pool, vertices_nr, graph_degree, adjacency_list);

        /*if (generations_without_improvement > 25) {
            // random_mutation(pop, graph_degree, mut_p);
            corrective_mutation_randomly(pop, graph_degree, mut_p, adjacency_list, vertices_nr);
            crossover_random_shuffle(pop, cx_prob);
            generations_without_improvement = 0;
        }
        else {
            corrective_mutation_on_every_conflict(pop, graph_degree, adjacency_list, vertices_nr);
            crossover_by_fitness(pop, cx_prob, adjacency_list);
            generations_without_improvement = 0;
        }*/

//        if (get_random_double(0, 1) <= 0.75) {
//            corrective_mutation_on_every_conflict(pop, graph_degree, adjacency_list, vertices_nr);
//        }
//        else {
//            corrective_mutation_randomly(pop, graph_degree, mut_p, adjacency_list, vertices_nr);
//        }

        // corrective_mutation_randomly(pop, graph_degree, mut_p, adjacency_list, vertices_nr);
        corrective_mutation_on_every_conflict(pop, graph_degree, adjacency_list, vertices_nr);
        crossover_by_fitness(pop, cx_prob, adjacency_list);

        // simple_crossover(pop);
        // crossover(pop, cx_prob);
        // crossover_by_fitness(pop, cx_prob, adjacency_list);
        // crossover_random_shuffle(pop, cx_prob);

        pop_values = calculate_conflict_fitness(pop, adjacency_list);
        std::vector<int> pop_values_as_colors = calculate_coloring_fitness(pop);

        for (size_t i{0}; i < pop_values_as_colors.size(); ++i) {
            if (pop_values_as_colors[i] < new_best_color_sol && pop_values[i] == 0) {
                new_best_color_sol = pop_values_as_colors[i];
            }
        }

        if (new_best_color_sol < best_color_nr) {
            best_color_nr = new_best_color_sol;
            generations_without_improvement = 0;
        }
        else {
            generations_without_improvement++;
        }
    }

    return best_color_nr;
}