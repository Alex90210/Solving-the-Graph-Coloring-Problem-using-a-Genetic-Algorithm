#ifndef GA_H
#define GA_H

#include "genetic_operators.h"
#include "generators.h"
#include "col_operators.h"

int genetic_algorithm(int pop_size, int elite_pool, int vertices_nr, int graph_degree, int max_gen,
                      const double& cx_prob, const std::vector<std::list<int>>& adjacency_list);

#endif