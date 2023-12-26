#ifndef AG_FITNESS_H
#define AG_FITNESS_H

#include <vector>
#include <list>
#include <set>
#include "col_operators.h"

std::vector<int> calculate_conflict_fitness(const std::vector<std::vector<int>>& population,
                                            const std::vector<std::list<int>>& adjacency_list);
std::vector<int> calculate_coloring_fitness(const std::vector<std::vector<int>>& population);
std::vector<int> calculate_col_fit_with_penalizing(const std::vector<std::vector<int>>& population,
                                                   const std::vector<std::list<int>>& adjacency_list);

#endif