# Parallel-Programming-Projects

This repository contains four projects developed as part of our college coursework in parallel programming.

## Table of Contents
1. [Genetic Algorithm for N-Queens Problem](#genetic-algorithm-for-n-queens-problem)
2. [Project 2: Project Title](#project-2-project-title)
3. [Project 3: Project Title](#project-3-project-title)
4. [Project 4: Project Title](#project-4-project-title)

### Description
This project implements a genetic algorithm to solve the N-Queens problem using parallel programming with OpenMP. The goal is to find a solution where 8 queens can be placed on a chessboard without attacking each other.

### Features
- Genetic Algorithm implementation
- Parallel initialization and evolution using OpenMP
- Fitness calculation based on non-attacking pairs of queens
- Crossover and mutation operations for generating new populations

### Installation and Usage
To compile and run the program, you need a C++ compiler with OpenMP support. Follow the steps below:

1. Clone the repository:
    ```bash
    git clone https://github.com/yourusername/parallel-programming-project.git
    cd parallel-programming-project
    ```

2. Navigate to the project directory:
    ```bash
    cd genetic-algorithm
    ```

3. Compile the program:
    ```bash
    g++ -fopenmp -o genetic_algorithm genetic_algorithm.cpp
    ```

4. Run the program:
    ```bash
    ./genetic_algorithm
    ```

### Code Snippets
Here is a brief code snippet from the project:

```cpp
struct Individual {
    std::vector<int> chromosome;
    int fitness;

    Individual() : fitness(0) {
        chromosome.resize(BOARD_SIZE);
    }
};

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
```

###ScreenShot
![Description of the image](./image.png)

