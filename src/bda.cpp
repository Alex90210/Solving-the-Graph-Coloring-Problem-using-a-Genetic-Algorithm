#include "../include/bsa.h"

std::vector<int> create_random_solution(int m_color, int num_vertices) {
    std::vector<int> solution;
    for (size_t i = 0; i < num_vertices; ++i) {
        int random_color = get_random_int(1, m_color);
        solution.push_back(random_color);
    }
    return solution;
}

int findVertexWithMaxConflict(const std::vector<int>& solution, const std::vector<std::list<int>>& adjacency_list) {
    int Vmc = -1;
    int maxConflict = 0;

    for (size_t i = 0; i < solution.size(); ++i) {
        int conflicts = 0;
        for (int adj : adjacency_list[i]) {
            if (solution[i] == solution[adj]) {
                conflicts++;
            }
        }
        if (conflicts > maxConflict) {
            maxConflict = conflicts;
            Vmc = i;
        }
    }
    return Vmc;
}

bool isValidSolution(const std::vector<int>& solution, const std::vector<std::list<int>>& adjacency_list) {
    for (size_t i = 0; i < solution.size(); ++i) {
        for (int adj : adjacency_list[i]) {
            if (solution[i] == solution[adj]) {
                return false;
            }
        }
    }
    return true;
}

int calculateCost(const std::vector<int>& solution) {
    std::unordered_set<int> distinctColors;

    for (int color : solution) {
        if (color != 0) {  // Exclude the default color, adjust if necessary
            distinctColors.insert(color);
        }
    }

    return distinctColors.size();
}

std::vector<int> get_available_colors(int vertex, const std::vector<int>& solution, const std::vector<std::list<int>>& adjacency_list) {
    std::vector<int> available_colors;
    int m_color = solution.size();

    for (int color = 1; color <= m_color; ++color) {
        bool conflict = false;
        for (int neighbor : adjacency_list[vertex]) {
            if (solution[neighbor] == color) {
                conflict = true;
                break;
            }
        }
        if (!conflict) {
            available_colors.push_back(color);
        }
    }

    return available_colors;
}

void repair(std::vector<int>& solution, const std::vector<std::list<int>>& adjacency_list, int& m_color) {

    while (!isValidSolution(solution, adjacency_list)) {
        int Vmc = findVertexWithMaxConflict(solution, adjacency_list);
        std::vector<int> availableColors = get_available_colors(Vmc, solution, adjacency_list);

        if (!availableColors.empty()) {
            int randomColor = availableColors[get_random_int(0, availableColors.size() - 1)];
            solution[Vmc] = randomColor;
        }

        m_color--;
    }
}

void rand_change_op(std::vector<int>& solution, std::vector<std::list<int>>& adjacency_list, int& m_color) {
    int x = get_random_int(0, solution.size() - 1);

    solution[x] = get_random_int(1, m_color);

    if (isValidSolution(solution, adjacency_list)) {
        m_color--;
    } else {
        // repair(solution, adjacency_list, m_color);
    }
}

int simulated_annealing(std::vector<std::list<int>>& adjacency_list) {
    double temperature = 1000;
    double cooling_rate {0.995};
    int m_color = find_max_degree(adjacency_list) + 1;
    std::vector<int> solution = create_random_solution(m_color, adjacency_list.size());

    int current_cost = calculateCost(solution);
    // repair(solution, adjacency_list, m_color);

    double last_print_temperature = temperature;

    while (temperature > 0) {
        std::vector<int> new_solution = solution;
        rand_change_op(new_solution, adjacency_list, m_color);

        int new_cost = calculateCost(new_solution);

        if (new_cost < current_cost) {
            solution = new_solution;
            current_cost = new_cost;
        } else {
            int delta = current_cost - new_cost;
            double probability = exp(-delta / temperature);

            if (probability > get_random_double(0, 1)) {
                solution = new_solution;
                current_cost = new_cost;
            }
        }

        if (last_print_temperature - temperature >= 1000) {
            std::cout << "Temperature: " << temperature << ", Current Cost: " << current_cost << std::endl;
            last_print_temperature = temperature;
        }

        // temperature -= 0.01;
        temperature *= cooling_rate;
    }

    return current_cost;
}