#ifndef AG_MUTATION_H
#define AG_MUTATION_H

#include <vector>
#include <list>
#include <set>
#include "col_operators.h"
#include "generators.h"

void corrective_mutation_on_every_conflict(std::vector<std::vector<int>>& population, const int& graph_degree,
                                           const std::vector<std::list<int>>& adjacency_list, const int& vertices_nr,
                                           double mutation_probability);
void corrective_mutation_randomly(std::vector<std::vector<int>>& population, const int& graph_degree,
                                  const double& mutation_probability,
                                  const std::vector<std::list<int>>& adjacency_list, const int& vertices_nr);
void random_mutation_on_every_conflict(std::vector<std::vector<int>>& population, const int& graph_degree,
                                       const std::vector<std::list<int>>& adjacency_list, const int& vertices_nr);
void random_mutation(std::vector<std::vector<int>>& population, const int& graph_degree,
                     const double& mutation_probability);
void corrective_mutation_population(std::vector<std::vector<int>>& population,
                                    const std::vector<std::list<int>>& adjacency_list,
                                    const int& max_color,
                                    const double& mutation_probability);
void corrective_mutation_until_valid(std::vector<std::vector<int>>& population,
                                     const std::vector<std::list<int>>& adjacency_list,
                                     const int& max_color,
                                     const int max_iterations = 1000);

#endif