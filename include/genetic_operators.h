#ifndef GENETIC_OPERATORS_H
#define GENETIC_OPERATORS_H

#include <vector>
#include "generators.h"
#include "utils.h"

void simple_crossover(std::vector<std::vector<int>>& population);
void crossover(std::vector<std::vector<int>>& population, const double& crossover_probability);
void crossover_by_fitness(std::vector<std::vector<int>>& population, const double& crossover_probability,
                          const std::vector<std::list<int>>& adjacency_list);
void crossover_random_shuffle(std::vector<std::vector<int>>& population, const double& crossover_probability);
void corrective_mutation(std::vector<std::vector<int>>& population, const int& graph_degree,
                         const std::vector<std::list<int>>& adjacency_list, const int& vertices_nr);
void random_mutation(std::vector<std::vector<int>>& population, const int& graph_degree,
                     const std::vector<std::list<int>>& adjacency_list, const int& vertices_nr);
std::vector<std::vector<int>> elitism(const std::vector<std::vector<int>>& population,
                                      const std::vector<int>& population_values,
                                      size_t elite_pool);
std::vector<std::vector<int>> selection(const std::vector<std::vector<int>>& pop,int pop_size, int elite_pool,
                                        const std::vector<std::list<int>>& adjacency_list);

#endif