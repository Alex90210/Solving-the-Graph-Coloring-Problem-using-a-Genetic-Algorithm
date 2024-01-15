#include "include/SA.h"

int main() {
    std::string filename = "../test_instances/queen7_7.col";
    std::vector<std::list<int>> adjacency_list;
    read_col_file(filename, adjacency_list);

    int max_degree = find_max_degree(adjacency_list);
    std::cout << "Max degree: " << max_degree << std::endl;

    int final_cost = simulated_annealing(adjacency_list);

    // Output the results
    std::cout << "Final cost (number of distinct colors): " << final_cost << std::endl;

    return 0;
}