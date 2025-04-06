#ifndef RANDOM_NUMBER_GENERATOR_H
#define RANDOM_NUMBER_GENERATOR_H

#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <limits>

class randomNumberGenerator {
private:
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist;

public:
    randomNumberGenerator()
        : gen(std::chrono::steady_clock::now().time_since_epoch().count()),
          dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()) {}

    std::vector<int> generateRandomArray(size_t size) {
        std::vector<int> arr(size);
        for (size_t i = 0; i < size; ++i) {
            arr[i] = dist(gen);
        }
        return arr;
    }

    std::vector<int> generatePartiallySortedArray(size_t size, double sortedFraction) {
        std::vector<int> data = generateRandomArray(size);
        if (sortedFraction > 0.0) {
            size_t sortedSize = static_cast<size_t>(size * sortedFraction);
            std::partial_sort(data.begin(), data.begin() + sortedSize, data.end());
        }
        return data;
    }

    std::vector<int> generateReversedArray(size_t size) {
        std::vector<int> data = generateRandomArray(size);
        std::sort(data.begin(), data.end(), std::greater<int>());
        return data;
    }
};

#endif