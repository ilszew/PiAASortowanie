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

std::vector<int> generateRandomArray(size_t size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, size);

    std::vector<int> arr(size);
    for (size_t i = 0; i < size; i++) {
        arr[i] = dist(gen);
    }
    return arr;
}

std::vector<int> generatePartiallySortedArray(std::size_t size, double sortedFraction) {
    std::vector<int> data = generateRandomArray(size);

    if (sortedFraction > 0.0) {
        std::size_t sortedSize = static_cast<std::size_t>(size * sortedFraction);
        std::partial_sort(data.begin(), data.begin() + sortedSize, data.end());
    }

    return data;
}

std::vector<int> generateReversedArray(std::size_t size) {
    std::vector<int> data = generateRandomArray(size);
    std::sort(data.begin(), data.end(), std::greater<int>());
    return data;
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

            const std::array<std::function<std::vector<int>(std::size_t)>, 8> testCaseGenerators = {
                generateRandomArray,
                [](std::size_t size) { return generatePartiallySortedArray(size, 0.25); },
                [](std::size_t size) { return generatePartiallySortedArray(size, 0.50); },
                [](std::size_t size) { return generatePartiallySortedArray(size, 0.75); },
                [](std::size_t size) { return generatePartiallySortedArray(size, 0.95); },
                [](std::size_t size) { return generatePartiallySortedArray(size, 0.99); },
                [](std::size_t size) { return generatePartiallySortedArray(size, 0.997); },
                generateReversedArray
            };


            for (std::size_t testCaseIndex = 0; testCaseIndex < testCaseNames.size(); ++testCaseIndex) {
                const std::string& testCaseName = testCaseNames[testCaseIndex];
                std::filesystem::path dirPath = "results/" + algorithm.name + "/" +
                                                std::to_string(arraySize) + "/" +
                                                testCaseName;

                std::filesystem::create_directories(dirPath);
                std::vector<int> testCase = testCaseGenerators[testCaseIndex](arraySize);

                for (int runIndex = 0; runIndex < 100; ++runIndex) {
                    std::vector<int> arrayCopy = testCase;

                    auto start = std::chrono::high_resolution_clock::now();
                    algorithm.sortFunction(arrayCopy);
                    auto end = std::chrono::high_resolution_clock::now();

                    if (!std::is_sorted(arrayCopy.begin(), arrayCopy.end())) {
                        std::cerr << "Sorting failed for: "
                            << algorithm.name << ", Size: " << arraySize
                            << ", Test Case: " << testCaseName << std::endl;
                        continue;
                    }

                    std::chrono::duration<double> diff = end - start;
                    std::filesystem::path resultFile = dirPath / (std::to_string(runIndex) + ".txt");

                    std::ofstream outFile(resultFile, std::ios::out | std::ios::trunc);
                    outFile << std::fixed << std::setprecision(9) << diff.count() << std::endl;
                    outFile.close();
                }
            }
        }

    }
    return 0;
}