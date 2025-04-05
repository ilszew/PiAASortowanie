#ifndef SORTING_ALGORITHMS_QUICKSORT_H
#define SORTING_ALGORITHMS_QUICKSORT_H

#include <vector>

template <typename T>
class QuickSort
{
public:
    typename std::vector<T>::iterator partition(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end) {
        if (end - start <= 1) return start;

        auto pivotIt = start + (end - start) / 2;
        T pivot = *pivotIt;

        std::swap(*pivotIt, *(end - 1));

        auto i = start;
        for (auto j = start; j < end - 1; ++j) {
            if (*j <= pivot) {
                std::swap(*i, *j);
                ++i;
            }
        }

        std::swap(*i, *(end - 1));
        return i;
    }

    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end) {
        if (end - start <= 1) return;

        auto pivot = partition(start, end);
        sort(start, pivot);
        sort(pivot + 1, end);
    }
};

#endif //SORTING_ALGORITHMS_QUICKSORT_H