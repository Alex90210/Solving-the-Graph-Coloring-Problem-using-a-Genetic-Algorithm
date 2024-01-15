#include "../include/generators.h"

int get_random_int(int min, int max) {
    static std::random_device rd;
    static std::mt19937 eng(rd());

    std::uniform_int_distribution<int> distribution(min, max);

    return distribution(eng);
}

double get_random_double(double min, double max) {
    static bool initialized = false;

    if (!initialized) {
        std::srand(static_cast<unsigned>(std::time(0)));
        initialized = true;
    }

    double random_normalized = static_cast<double>(std::rand()) / RAND_MAX;
    return min + random_normalized * (max - min);
}

int select_index(const std::vector<double>& cumulative_probabilities) {
    double random_value = get_random_double(0, 1);

    auto it = std::lower_bound(cumulative_probabilities.begin(), cumulative_probabilities.end(), random_value);
    int selected_index = std::distance(cumulative_probabilities.begin(), it);

    return selected_index;
}

/*std::vector<std::vector<int>> generate_population(const unsigned& population_size, int nr_of_nodes, const int& graph_degree) {

    std::vector<std::vector<int>> generated_population;

    for (size_t i {0}; i < population_size; ++i) {
        std::vector<int> chromosome;
        for (size_t j {0}; j < nr_of_nodes; ++j) {
            // I'm starting from 0, there is no need to add 1 to satisfy Brook's theorem
            int random_color = get_random_int(0, graph_degree);
            chromosome.push_back(random_color);
        }
        generated_population.push_back(chromosome);
    }

    return generated_population;
}*/

std::mt19937& get_random_engine() {
    // Static ensures the variable is only initialized once and persists between calls
    static std::mt19937 engine;

    // Seed the engine only once
    static bool isSeeded = false;
    if (!isSeeded) {
        // Use current time as a seed for the random number generator
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        engine.seed(seed);
        isSeeded = true;
    }

    return engine;
}

/*std::vector<std::vector<int>> generate_population(const unsigned& population_size, int nr_of_nodes, const int& graph_degree) {
    std::vector<std::vector<int>> generated_population;
    std::vector<int> base_chromosome(nr_of_nodes);

    // Initialize base chromosome with distinct colors
    for (int i = 0; i < nr_of_nodes; ++i) {
        base_chromosome[i] = i;
    }

    for (size_t i = 0; i < population_size; ++i) {
        // Shuffle the base chromosome to get a new random sequence of colors
        std::shuffle(base_chromosome.begin(), base_chromosome.end(), get_random_engine());

        // Add the shuffled chromosome to the population
        generated_population.push_back(base_chromosome);
    }

    return generated_population;
}*/

std::vector<std::vector<int>> generate_population(const unsigned& population_size, int nr_of_nodes, int graph_degree, int color_number) {
    std::vector<std::vector<int>> generated_population;

    for (size_t i = 0; i < population_size; ++i) {
        std::vector<int> chromosome;
        for (size_t j = 0; j < graph_degree; ++j) {
            int random_color = get_random_int(0, color_number);
            chromosome.push_back(random_color);
        }
        generated_population.push_back(chromosome);
    }

    return generated_population;
}

std::vector<std::vector<int>> get_two_random_parents(const std::vector<std::vector<int>>& population) {

    int first_random_index = get_random_int(0, population.size() - 1);
    int second_random_index = first_random_index;

    while (second_random_index == first_random_index) {
        second_random_index = get_random_int(0, population.size() - 1);
    }

    return {population[first_random_index], population[second_random_index]};
}