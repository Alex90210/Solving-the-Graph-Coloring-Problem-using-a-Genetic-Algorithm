#ifndef COL_OPERATORS_H
#define COL_OPERATORS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <unordered_set>

void read_col_file(const std::string& filename, std::vector<std::list<int>>& adjacencyList);
int find_max_degree(const std::vector<std::list<int>>& adjacencyList);
int count_vertices(const std::vector<std::list<int>>& adjacencyList);
bool has_same_color_neighbor(int vertex, const std::vector<int>& colors, const std::vector<std::list<int>>& adjacencyList);
std::vector<int> get_adjacent_colors(int vertex, const std::vector<int>& chromosome,
                                     const std::vector<std::list<int>>& adjacency_list);
std::vector<int> create_color_vector(int graph_degree);
std::vector<int> find_non_adjacent_colors(const std::vector<int>& all_colors, const std::vector<int>& adjacent_colors);
std::vector<int> calculate_conflict_fitness(const std::vector<std::vector<int>>& population,
                                            const std::vector<std::list<int>>& adjacency_list);
std::vector<int> calculate_coloring_fitness(const std::vector<std::vector<int>>& population);
int get_coloring_number(const std::vector<int>& chromosome);

#endif