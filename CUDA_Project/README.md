# CUDA Project: Pattern Matching in Text

## Introduction
This project demonstrates the use of CUDA for parallel programming by implementing a simple pattern matching algorithm. The goal is to identify the positions of a specified pattern within a given text using the parallel processing capabilities of GPUs.

## Objectives
- To understand the basics of GPU programming with CUDA.
- To implement a parallel pattern matching algorithm using CUDA.
- To compare the performance of the parallel algorithm with its serial counterpart.

## Implementation
The project uses CUDA to parallelize the process of pattern matching in a text. The key components of the implementation are:

- **Text Input:** The text in which to search for the pattern.
- **Pattern Input:** The pattern to search for within the text.
- **CUDA Kernel:** A kernel function that performs the pattern matching in parallel on the GPU.

## Files
- `kernel.cu`: Contains the CUDA code for the pattern matching algorithm.

## How to Run
1. **Clone the repository:**
   ```sh
   git clone https://github.com/yourusername/your-repo.git
   cd your-repo
   ```
2. **Compile the CUDA code:**
   ```sh
   nvcc -o pattern_matching kernel.cu

   ```
3. **Run the executable:**
   ```sh
   ./pattern_matching
   ```

## How to run using Visual Studio 2022

1. **Open the project in Visual Studio 2022.**
- Ensure you have the CUDA toolkit installed and properly configured with Visual Studio.

2. **Set up the project:**
- Right-click on the project in the Solution Explorer and select Properties.
- Navigate to Configuration Properties -> CUDA C/C++ -> Device and ensure that the CUDA Toolkit is set to the correct version.

3. **Build and run the project:**
- Click on the Start Debugging button (usually a green arrow or "Local Windows Debugger") in the toolbar.
- Alternatively, press F5 to build and run the CUDA program in debug mode.

4. **View the output:**
- The program output should appear in the console window, displaying the results of the CUDA computation.

## Example Output

![Alt text](https://raw.githubusercontent.com/SuzenFirasta/Parallel-Programming-Projects/main/CUDA_Project/images/image.png)



## Conclusion
This project showcases the use of CUDA for parallel pattern matching, highlighting the potential performance improvements that can be achieved with GPU programming. Further enhancements can include more complex pattern matching algorithms and performance optimizations.
