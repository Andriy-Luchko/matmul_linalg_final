#include <iostream>
#include <vector>
#include <iterator>
#include <ranges>
#include <memory>
#include <random>
#include <algorithm>
#include <chrono>
#include <fstream>

void run_all_mat_muls(size_t size);
void fill_with_random(int* matrix, size_t size);
void ijk_matmul(const int* A, const int* B, int* C, size_t size);
void ikj_matmul(const int* A, const int* B, int* C, size_t size);
void append_to_csv(const std::string& function_name, size_t size, double time);

int main() {
    for (size_t size = 1; size <= 1 << 10; ++size) {
        run_all_mat_muls(size);
    }
    return 0;
}

void run_all_mat_muls(size_t size) {
    auto A = std::make_unique<int[]>(size * size);
    auto B = std::make_unique<int[]>(size * size);
    auto C = std::make_unique<int[]>(size * size);

    fill_with_random(A.get(), size);
    fill_with_random(B.get(), size);

    std::fill(C.get(), C.get() + (size * size), 0);
    ijk_matmul(A.get(), B.get(), C.get(), size);

    std::fill(C.get(), C.get() + (size * size), 0);
    ikj_matmul(A.get(), B.get(), C.get(), size);

    std::cout << "Matrix multiplication completed for size " << size << "x" << size << "\n";
}

void fill_with_random(int* matrix, size_t size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 100);

    for (size_t i = 0; i < size * size; ++i) {
        matrix[i] = dist(gen);
    }
}

void ijk_matmul(const int* A, const int* B, int* C, size_t size) {
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            for (size_t k = 0; k < size; ++k) {
                C[i * size + j] += A[i * size + k] * B[k * size + j];
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    double time_in_seconds = duration.count();

    append_to_csv("ijk_matmul", size, time_in_seconds);

    std::cout << "Matrix multiplication for size " << size << "x" << size 
              << " completed in " << time_in_seconds << " seconds.\n";
}

void ikj_matmul(const int* A, const int* B, int* C, size_t size) {
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < size; ++i) {
        for (size_t k = 0; k < size; ++k) {
            for (size_t j = 0; j < size; ++j) {
                C[i * size + j] += A[i * size + k] * B[k * size + j];
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    double time_in_seconds = duration.count();

    append_to_csv("ikj_matmul", size, time_in_seconds);

    std::cout << "Matrix multiplication for size " << size << "x" << size 
              << " completed in " << time_in_seconds << " seconds.\n";
}

void append_to_csv(const std::string& function_name, size_t size, double time) {
    std::ofstream file("data/times.csv", std::ios_base::app);
    if (file.is_open()) {
        if (file.tellp() == 0) {
            file << "function_name,size,time_seconds\n";
        }
        file << function_name << "," << size << "," << time << "\n";
        file.close();
    } else {
        std::cerr << "Error opening the file for writing.\n";
    }
}
