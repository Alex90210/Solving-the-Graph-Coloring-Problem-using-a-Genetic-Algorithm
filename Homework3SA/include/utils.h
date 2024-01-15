#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <list>
#include <fstream>
#include <sstream>
#include <random>
#include <unordered_set>
#include <ctime>

void read_col_file(const std::string& filename, std::vector<std::list<int>>& adjacency_list);
int get_random_int(int min, int max);
int find_max_degree(const std::vector<std::list<int>>& adjacencyList);
double get_random_double(double min, double max);

#endif