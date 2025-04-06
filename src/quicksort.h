#ifndef SORTING_ALGORITHMS_QUICKSORT_H
#define SORTING_ALGORITHMS_QUICKSORT_H

#include <vector>
#include <algorithm>

template <typename T>
class QuickSort
{
public:
    typename std::vector<T>::iterator partition(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end) {
        if (start >= end - 1) return start;

        auto size = end - start;
        auto mid = start + size / 2;
        auto last = end - 1;

        if (*mid < *start) std::swap(*start, *mid);
        if (*last < *start) std::swap(*start, *last);
        if (*last < *mid) std::swap(*mid, *last);

        T pivot = *mid;
        std::swap(*mid, *(end - 2));

        auto i = start;
        auto j = end - 2;

        for (;;) {
            while (*(++i) < pivot);
            while (pivot < *(--j));
            if (i >= j) break;
            std::swap(*i, *j);
        }

        std::swap(*i, *(end - 2));

        return i;
    }

    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end) {
        if (end - start <= 1) return;

        if (end - start == 2) {
            if (*(end - 1) < *start)
                std::swap(*start, *(end - 1));
            return;
        }

        auto pivot = partition(start, end);
        sort(start, pivot);
        sort(pivot + 1, end);
    }
};

#endif //SORTING_ALGORITHMS_QUICKSORT_H