#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <algorithm>
#include <functional>
#include <chrono>
#include "mergesort.h"
#include "quicksort.h"
#include "introsort.h"

struct sortAlgorithm {
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

    std::vector<int> tab(size);
    for (size_t i = 0; i < size; i++) {
        tab[i] = dist(gen);
    }
    return tab;
}

std::vector<int> generatePartiallySortedArray(size_t size, double sortedFraction) {
    std::vector<int> data = generateRandomArray(size);

    if (sortedFraction > 0.0) {
        size_t sortedSize = static_cast<size_t>(size * sortedFraction);
        sort(data.begin(), data.begin() + sortedSize);
    }

    return data;
}

std::vector<int> generateReversedArray(size_t size) {
    std::vector<int> data = generateRandomArray(size);
    sort(data.begin(), data.end(), std::greater<int>());
    return data;
}

int main() {
    const int arraysSizes[5] = {10000, 50000, 100000, 500000, 1000000};

    sortAlgorithm sortAlgorithms[] = {
        {"MergeSort", mergeSortWrapper},
        {"QuickSort", quickSortWrapper},
        {"IntroSort", introSortWrapper}
    };

    for (const auto& algorithm : sortAlgorithms) {

        // petla dla kazdej wielkosci tablic
        for (int i = 0; i < sizeof(arraysSizes) / sizeof(arraysSizes[0]); i++) {

            std::vector<std::vector<int>> testCases = {
                generateRandomArray(i),
                generatePartiallySortedArray(i, 0.25),
                generatePartiallySortedArray(i, 0.50),
                generatePartiallySortedArray(i, 0.75),
                generatePartiallySortedArray(i, 0.95),
                generatePartiallySortedArray(i, 0.99),
                generatePartiallySortedArray(i, 0.997),
                generateReversedArray(i)
            };


            for (std::vector<int>& testCase : testCases) {









            }

        }

    }
    return 0;
}