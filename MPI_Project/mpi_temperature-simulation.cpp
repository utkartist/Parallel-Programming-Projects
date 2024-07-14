#include <mpi.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <numeric>

// Function to simulate one timestep
void simulate_step(std::vector<float>& local_grid, float left_neighbor, float right_neighbor) {
    std::vector<float> new_local_grid = local_grid;
    for (size_t i = 0; i < local_grid.size(); ++i) {
        float left_temp = (i == 0) ? left_neighbor : local_grid[i - 1];
        float right_temp = (i == local_grid.size() - 1) ? right_neighbor : local_grid[i + 1];
        new_local_grid[i] = (local_grid[i] + left_temp + right_temp) / 3.0f;
    }
    local_grid.swap(new_local_grid); // Efficiently update local_grid with the contents of new_local_grid
}

// Function to print summary statistics
void print_summary(int timestep, const std::vector<float>& global_grid) {
    float min_temp = *std::min_element(global_grid.begin(), global_grid.end());
    float max_temp = *std::max_element(global_grid.begin(), global_grid.end());
    float average_temp = std::accumulate(global_grid.begin(), global_grid.end(), 0.0f) / global_grid.size();

    std::cout << "Timestep " << timestep << " Summary:\n";
    std::cout << "  Average Temperature: " << average_temp << " degrees\n";
    std::cout << "  Minimum Temperature: " << min_temp << " degrees\n";
    std::cout << "  Maximum Temperature: " << max_temp << " degrees\n";
    std::cout << "------------------------------------------\n";
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int grid_size_per_process = 10; // Number of grid cells per process
    std::vector<float> local_grid(grid_size_per_process, 25.0f); // Initialize with uniform temperature

    for (int timestep = 0; timestep < 100; ++timestep) {
        float left_boundary = world_rank == 0 ? 15.0f : local_grid.front();
        float right_boundary = world_rank == world_size - 1 ? 35.0f : local_grid.back();
        float left_neighbor, right_neighbor;

        MPI_Sendrecv(&right_boundary, 1, MPI_FLOAT, (world_rank + 1) % world_size, 0,
            &left_neighbor, 1, MPI_FLOAT, (world_rank - 1 + world_size) % world_size, 0,
            MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        MPI_Sendrecv(&left_boundary, 1, MPI_FLOAT, (world_rank - 1 + world_size) % world_size, 0,
            &right_neighbor, 1, MPI_FLOAT, (world_rank + 1) % world_size, 0,
            MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        simulate_step(local_grid, left_neighbor, right_neighbor);

        if (timestep % 10 == 0) {
            std::vector<float> global_grid;
            if (world_rank == 0) {
                global_grid.resize(grid_size_per_process * world_size);
            }
            MPI_Gather(local_grid.data(), grid_size_per_process, MPI_FLOAT,
                global_grid.data(), grid_size_per_process, MPI_FLOAT,
                0, MPI_COMM_WORLD);

            if (world_rank == 0) {
                print_summary(timestep, global_grid);
            }
        }
    }

    MPI_Finalize();
    return 0;
}
