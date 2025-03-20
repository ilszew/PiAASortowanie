#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <algorithm>
#include <functional>
#include <chrono>
#include "mergesort.h"
#include "quicksort.h"
#include "introsort.h"

std::vector<int> generateRandomArray(size_t size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, size);

    std::vector<int> tablica(size);
    for (size_t i = 0; i < size; i++) {
        tablica[i] = dist(gen);
    }
    return tablica;
}

int main() {
    const int arraysSizes[5] = {10000, 50000, 100000, 500000, 1000000};

    //petla na sortowania

    for (;;) {

        // petla dla kazdej wielkosci tablic
        for (int i = 0; i < sizeof(arraysSizes) / sizeof(arraysSizes[0]); i++) {

            //petla dla kazdego przypadku

            for ( ; ; ) {









            }

        }

    }
    return 0;
}