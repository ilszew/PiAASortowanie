#ifndef SORTING_ALGORITHMS_INTROSORT_H
#define SORTING_ALGORITHMS_INTROSORT_H

#include <vector>
#include <cmath>
#include "quicksort.h"
#include "insertsort.h"
#include "heapsort.h"

template <typename T>
class IntroSort
{
public:
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        int maxDepth = 2 * std::log(std::distance(start, end));
        introsort(start, end, maxDepth);
    }

private:
    void introsort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end, int depth)
    {
        if (std::distance(start, end) <= 16)
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

        QuickSort<T> quickSort;
        typename std::vector<T>::iterator partition_point = quickSort.partition(start, end);

        introsort(start, partition_point, depth - 1);
        introsort(partition_point, end, depth - 1);
    }
};

#endif //SORTING_ALGORITHMS_INTROSORT_H