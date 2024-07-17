#include <iostream>
#include <cuda_runtime.h>
#include <stdio.h>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include "device_launch_parameters.h"



#define BLOCK_SIZE 256

__global__ void matchPattern(const char* text, int textLen, const char* pattern, int patternLen, int* positions) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx + patternLen <= textLen) {
        bool match = true;
        for (int i = 0; i < patternLen && match; ++i) {
            if (text[idx + i] != pattern[i]) {
                match = false;
            }
        }
        if (match) {
            positions[idx] = 1;
        }
    }
}

void printMatches(const int* positions, int textLen, const std::string& text, const std::string& pattern) {
    for (int i = 0; i < textLen; ++i) {
        if (positions[i] == 1) {
            std::cout << "Pattern \"" << pattern << "\" found at position " << i << " in text \"" << text << "\"" << std::endl;
        }
    }
}

int main() {
    std::string text = "hello world, CUDA welcome to CUDA programming";
    std::string pattern = "CUDA";
    int textLen = text.size();
    int patternLen = pattern.size();

    char* d_text, * d_pattern;
    int* d_positions, * positions;

    cudaMalloc(&d_text, textLen);
    cudaMalloc(&d_pattern, patternLen);
    cudaMalloc(&d_positions, textLen * sizeof(int));

    cudaMemcpy(d_text, text.c_str(), textLen, cudaMemcpyHostToDevice);
    cudaMemcpy(d_pattern, pattern.c_str(), patternLen, cudaMemcpyHostToDevice);

    // Initialize positions array to 0
    positions = new int[textLen]();
    cudaMemcpy(d_positions, positions, textLen * sizeof(int), cudaMemcpyHostToDevice);

    int blocks = (textLen + BLOCK_SIZE - 1) / BLOCK_SIZE;
    matchPattern << <blocks, BLOCK_SIZE >> > (d_text, textLen, d_pattern, patternLen, d_positions);

    cudaMemcpy(positions, d_positions, textLen * sizeof(int), cudaMemcpyDeviceToHost);

    printMatches(positions, textLen, text, pattern);

    cudaFree(d_text);
    cudaFree(d_pattern);
    cudaFree(d_positions);
    delete[] positions;

    return 0;
}
