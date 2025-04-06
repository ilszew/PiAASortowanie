#ifndef SORTING_ALGORITHMS_INTROSORT_H
#define SORTING_ALGORITHMS_INTROSORT_H

#include <vector>
#include <cmath>
#include <algorithm>
#include "quicksort.h"
#include "insertsort.h"
#include "heapsort.h"

template <typename T>
class IntroSort
{
public:
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        if (start >= end) return;
        int maxDepth = 2 * static_cast<int>(std::log2(end - start));
        introsort(start, end, maxDepth);
    }

private:
    void introsort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end, int depth)
    {
        auto size = std::distance(start, end);

        if (size <= 16)
        {
            InsertSort<T> insertSort;
            insertSort.sort(start, end);
            return;
        }

        if (depth == 0)
        {
            HeapSort<T> heapSort;
            heapSort.sort(start, end);
            return;
        }

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

        introsort(start, i, depth - 1);
        introsort(i + 1, end, depth - 1);
    }
};

#endif //SORTING_ALGORITHMS_INTROSORT_H