
# MPI Project: Parallel Pattern Matching in Text

## Introduction
This project demonstrates the use of MPI (Message Passing Interface) for parallel programming by implementing a simple pattern matching algorithm. The goal is to identify the positions of a specified pattern within a given text using the parallel processing capabilities of multiple processors.

## Objectives
- To understand the basics of parallel programming with MPI.
- To implement a parallel pattern matching algorithm using MPI.
- To compare the performance of the parallel algorithm with its serial counterpart.

## Implementation
The project uses MPI to parallelize the process of pattern matching in a text. The key components of the implementation are:

- **Text Input:** The text in which to search for the pattern.
- **Pattern Input:** The pattern to search for within the text.
- **MPI Processes:** Multiple processes working together to perform the pattern matching.

## Files
- `mpi_pattern_matching.cpp`: Contains the MPI code for the pattern matching algorithm.

## How to Run

### Using Command Line
1. **Clone the repository:**
   ```sh
   git clone https://github.com/yourusername/your-repo.git
   cd your-repo/MPI_Project
2. **Compile the MPI code:**
   ```sh
    mpic++ -o mpi_pattern_matching mpi_pattern_matching.cpp
   ```
3. **Run the executable:**
   ```sh
   mpirun -np 4 ./mpi_pattern_matching
   ```

## Using Visual Studio 2022

- Open the “Property Pages” (Project -> Properties).
- Add the following in the **C/C++ >> General >> Additional Include Directories** area:
  - For x64: `$(MSMPI_INC);$(MSMPI_INC)\x64`
  - For x86: `$(MSMPI_INC);$(MSMPI_INC)\x86`

Apply the changes.
![Step1](https://github.com/kartabyakrishna/KartabyaKrishna/blob/main/Assets/mpi-setup/step1.gif)

## 8. Set up the linker library

Add `msmpi.lib` to the **Linker >> Input >> Additional Dependencies** . Remember to add a semicolon after `msmpi.lib`.
![Step2](https://github.com/kartabyakrishna/KartabyaKrishna/blob/main/Assets/mpi-setup/step2.gif)

## 9. Additional Library Directories

Add the following to the **Linker >> General >> Additional Library Directories** :
- For x64: `$(MSMPI_LIB64)`
- For x86: `$(MSMPI_LIB32)`
![Step3](https://github.com/kartabyakrishna/KartabyaKrishna/blob/main/Assets/mpi-setup/step3.gif)
## 10. Build the solution

Build the solution (Build -> Build Solution).
![Build Solution](https://github.com/kartabyakrishna/KartabyaKrishna/blob/main/Assets/mpi-setup/build%20Soln.png)

## 11. Test the program

To test or execute the program, go to the Debug directory and execute the following commands:

```bash
mpiexec –n <number_of_processing_elements> ./<executable_file>
```
![Build Soln](https://github.com/kartabyakrishna/KartabyaKrishna/blob/main/Assets/mpi-setup/output%20using%20mpiexec.png)

Replace `<number_of_processing_elements>` and `<executable_file>` accordingly.
