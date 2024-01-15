#ifndef GENERATORS_H
#define GENERATORS_H

#include <vector>
#include <iostream>
#include <random>
#include <chrono>
#include "col_operators.h"

int get_random_int(int min, int max);
double get_random_double(double min, double max);
int select_index(const std::vector<double>& cumulative_probabilities);
std::vector<std::vector<int>> generate_population(const unsigned& population_size, int nr_of_nodes, int graph_degree, int color_number);
std::vector<std::vector<int>> get_two_random_parents(const std::vector<std::vector<int>>& population);

#endif