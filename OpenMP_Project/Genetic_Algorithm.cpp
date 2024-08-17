#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <omp.h>

const int BOARD_SIZE = 8;
const int POP_SIZE = 100;
const int MAX_GEN = 10000;
const float MUTATION_RATE = 0.1f;
const float CROSSOVER_RATE = 0.8f;

struct Individual {
    std::vector<int> chromosome;
    int fitness;

    Individual() : fitness(0) {
        chromosome.resize(BOARD_SIZE);
    }
};

bool compareIndividuals(const Individual& a, const Individual& b) {
    return a.fitness > b.fitness; // Sort in descending order of fitness
}

// Initialize a random individual
void initializeIndividual(Individual& individual) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        individual.chromosome[i] = std::rand() % BOARD_SIZE;
    }
}

// Calculate fitness
int calculateFitness(const Individual& individual) {
    int clashes = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = i + 1; j < BOARD_SIZE; ++j) {
            if (individual.chromosome[i] == individual.chromosome[j] || 
                abs(individual.chromosome[i] - individual.chromosome[j]) == j - i) {
                clashes++;
            }
        }
    }
    return 28 - clashes; // 28 is the max number of non-attacking pairs
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    std::vector<Individual> population(POP_SIZE);
    int generation = 0;

    // Initialize population in parallel
    #pragma omp parallel for
    for (int i = 0; i < population.size(); ++i) {
        initializeIndividual(population[i]);
        population[i].fitness = calculateFitness(population[i]);
    }

    while (generation < MAX_GEN) {
        // Sort population in descending order of fitness
        std::sort(population.begin(), population.end(), compareIndividuals);

        // Check for a solution
        if (population[0].fitness == 28) {
            std::cout << "Solution found in generation " << generation << ": ";
            for (size_t i = 0; i < population[0].chromosome.size(); ++i) {
                std::cout << population[0].chromosome[i] << " ";
            }
            std::cout << "\nFitness: " << population[0].fitness << std::endl;
            return 0;
        }

        // Create a new generation
        std::vector<Individual> newPopulation(population.size());

        #pragma omp parallel for
        for (int i = 0; i < POP_SIZE; i += 2) {
            Individual parent1 = population[std::rand() % POP_SIZE];
            Individual parent2 = population[std::rand() % POP_SIZE];
            Individual offspring1, offspring2;

            // Crossover
            int crossoverPoint = std::rand() % BOARD_SIZE;
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (j < crossoverPoint) {
                    offspring1.chromosome[j] = parent1.chromosome[j];
                    offspring2.chromosome[j] = parent2.chromosome[j];
                } else {
                    offspring1.chromosome[j] = parent2.chromosome[j];
                    offspring2.chromosome[j] = parent1.chromosome[j];
                }
            }

            // Mutation
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if ((static_cast<float>(std::rand()) / RAND_MAX) < MUTATION_RATE) {
                    offspring1.chromosome[j] = std::rand() % BOARD_SIZE;
                    offspring2.chromosome[j] = std::rand() % BOARD_SIZE;
                }
            }

            offspring1.fitness = calculateFitness(offspring1);
            offspring2.fitness = calculateFitness(offspring2);

            // Add to new population, ensuring thread safety for the push_back operation
            #pragma omp critical
            {
                newPopulation[i] = offspring1;
                if (i + 1 < POP_SIZE) {
                    newPopulation[i + 1] = offspring2;
                }
            }
        }

        population.swap(newPopulation);
        ++generation;
    }

    std::cout << "Solution not found in " << MAX_GEN << " generations." << std::endl;
    return 0;
}

