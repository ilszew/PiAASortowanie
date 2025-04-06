#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <filesystem>
#include <chrono>
#include "mergesort.h"
#include "quicksort.h"
#include "introsort.h"
#include "randomNumberGenerator.h"

struct SortAlgorithm {
    std::string name;
    void (*sortFunction)(std::vector<int>&);
};

void mergeSortWrapper(std::vector<int>& arr) {
    MergeSort<int> sorter;
    sorter.sort(arr.begin(), arr.end());
}

void quickSortWrapper(std::vector<int>& arr) {
    QuickSort<int> sorter;
    sorter.sort(arr.begin(), arr.end());
}

void introSortWrapper(std::vector<int>& arr) {
    IntroSort<int> sorter;
    sorter.sort(arr.begin(), arr.end());
}

int main() {
    const std::array<std::size_t, 5> arraySizes = {10000, 50000, 100000, 500000, 1000000};
    const std::array<SortAlgorithm, 3> sortAlgorithms = {{
        {"MergeSort", mergeSortWrapper},
        {"QuickSort", quickSortWrapper},
        {"IntroSort", introSortWrapper}
    }};


    std::filesystem::create_directory("results");

    for (const auto& algorithm : sortAlgorithms) {
        std::filesystem::create_directory("results/" + algorithm.name);

        for (const auto& arraySize : arraySizes) {
            std::filesystem::create_directory("results/" + algorithm.name + "/" + std::to_string(arraySize));

            const std::array<std::string, 8> testCaseNames = {
                "random_100",
                "sorted_25",
                "sorted_50",
                "sorted_75",
                "sorted_95",
                "sorted_99",
                "sorted_99_7",
                "reverse_sorted"
            };

            randomNumberGenerator generator(arraySize);

            const std::array<std::function<std::vector<int>()>, 8> testCaseGenerators = {
                [&]() { return generator.generateRandomArray(arraySize); },
                [&]() { return generator.generatePartiallySortedArray(arraySize, 0.25); },
                [&]() { return generator.generatePartiallySortedArray(arraySize, 0.50); },
                [&]() { return generator.generatePartiallySortedArray(arraySize, 0.75); },
                [&]() { return generator.generatePartiallySortedArray(arraySize, 0.95); },
                [&]() { return generator.generatePartiallySortedArray(arraySize, 0.99); },
                [&]() { return generator.generatePartiallySortedArray(arraySize, 0.997); },
                [&]() { return generator.generateReversedArray(arraySize); }
            };

            for (std::size_t testCaseIndex = 0; testCaseIndex < testCaseNames.size(); ++testCaseIndex) {
                const std::string& testCaseName = testCaseNames[testCaseIndex];
                std::filesystem::path resultFile = "results/" + algorithm.name + "/" + std::to_string(arraySize) + "/" + testCaseName + ".txt";
                std::ofstream outFile(resultFile, std::ios::out | std::ios::trunc);

                for (int runIndex = 0; runIndex < 100; ++runIndex) {
                    std::vector<int> arrayCopy = testCaseGenerators[testCaseIndex]();
                    auto start = std::chrono::high_resolution_clock::now();
                    algorithm.sortFunction(arrayCopy);
                    auto end = std::chrono::high_resolution_clock::now();

                    std::chrono::duration<double> diff = end - start;
                    outFile << std::fixed << std::setprecision(9) << diff.count() << std::endl;
                }
                outFile.close();
            }
        }
    }
    return 0;
}
