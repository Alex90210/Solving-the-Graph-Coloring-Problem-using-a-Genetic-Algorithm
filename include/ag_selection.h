#ifndef AG_SELECTION_H
#define AG_SELECTION_H

#include <vector>
#include <list>
#include <numeric>
#include "generators.h"
#include "ag_fitness.h"
#include "col_operators.h"
#include "utils.h"

std::vector<std::vector<int>> elitism(const std::vector<std::vector<int>>& population,
                                      const std::vector<int>& population_values,
                                      size_t elite_pool);
std::vector<std::vector<int>> selection(const std::vector<std::vector<int>>& pop,int pop_size, int elite_pool,
                                        int nr_vertices, int graph_degree,
                                        const std::vector<std::list<int>>& adjacency_list, int best_colorization);

#endif