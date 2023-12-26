#ifndef AG_MUTATION_H
#define AG_MUTATION_H

#include <vector>
#include <list>
#include "col_operators.h"
#include "generators.h"

void corrective_mutation_on_every_conflict(std::vector<std::vector<int>>& population, const int& graph_degree,
                                           const std::vector<std::list<int>>& adjacency_list, const int& vertices_nr);
void corrective_mutation_randomly(std::vector<std::vector<int>>& population, const int& graph_degree,
                                  const double& mutation_probability,
                                  const std::vector<std::list<int>>& adjacency_list, const int& vertices_nr);
void random_mutation_on_every_conflict(std::vector<std::vector<int>>& population, const int& graph_degree,
                                       const std::vector<std::list<int>>& adjacency_list, const int& vertices_nr);

#endif