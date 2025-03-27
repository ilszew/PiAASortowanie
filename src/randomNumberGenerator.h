#ifndef UNIQUE_RANDOM_GENERATOR_H
#define UNIQUE_RANDOM_GENERATOR_H

#include <vector>
#include <random>
#include <chrono>
#include <limits>

class UniqueRandomGenerator {
private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<long long> dist;
    long long seed;

public:
    UniqueRandomGenerator(size_t size) : 
        gen(rd()), 
        dist(0, std::numeric_limits<long long>::max()),
        seed(std::chrono::steady_clock::now().time_since_epoch().count()) 
    {
        gen.seed(seed);
    }

    std::vector<int> generateRandomArray(size_t size) {
        std::vector<int> arr(size);
        for (size_t i = 0; i < size; ++i) {
            arr[i] = static_cast<int>(dist(gen) ^ (i * seed));
        }
        return arr;
    }

    std::vector<int> generatePartiallySortedArray(size_t size, double sortedFraction) {
        std::vector<int> data = generateRandomArray(size);

        if (sortedFraction > 0.0) {
            std::size_t sortedSize = static_cast<std::size_t>(size * sortedFraction);
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

#endif // UNIQUE_RANDOM_GENERATOR_H