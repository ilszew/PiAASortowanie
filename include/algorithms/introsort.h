#ifndef SORTING_ALGORITHMS_INTROSORT_H
#define SORTING_ALGORITHMS_INTROSORT_H
#include <vector>
#include <cmath>
#include "quicksort.h"
#include "insertsort.h"
#include "heapsort.h"

// sortowanie introspektywne

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
        quickSort.sort(start, end);
    }
};
#endif //SORTING_ALGORITHMS_INTROSORT_H
