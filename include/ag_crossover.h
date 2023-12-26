#ifndef AG_CROSSOVER_H
#define AG_CROSSOVER_H

#include <vector>
#include "generators.h"
#include "ag_fitness.h"

void simple_crossover(std::vector<std::vector<int>>& population);
void crossover(std::vector<std::vector<int>>& population, const double& crossover_probability);
void crossover_by_fitness(std::vector<std::vector<int>>& population, const double& crossover_probability,
                          const std::vector<std::list<int>>& adjacency_list);
void crossover_random_shuffle(std::vector<std::vector<int>>& population, const double& crossover_probability);

#endif