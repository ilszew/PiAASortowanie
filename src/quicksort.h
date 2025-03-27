#ifndef SORTING_ALGORITHMS_QUICKSORT_H
#define SORTING_ALGORITHMS_QUICKSORT_H

#include <vector>

template <typename T>
class QuickSort
{
private:
    typename std::vector<T>::iterator choosePivot(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end) {
        auto mid = start + (end - start - 1) / 2;
        end--;

        if (*start > *mid) std::swap(*start, *mid);
        if (*mid > *end) std::swap(*mid, *end);
        if (*start > *mid) std::swap(*start, *mid);

        // Put the median at the end
        std::swap(*mid, *end);
        return end;
    }

    void quickSort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end) {
        if (end - start > 1) {
            auto pivot = partition(start, end);
            quickSort(start, pivot);
            quickSort(pivot + 1, end);
        }
    }

public:
    typename std::vector<T>::iterator partition(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end) {
        if (end - start <= 1) return start;

        auto pivotIt = choosePivot(start, end);
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
        if (start < end) {
            quickSort(start, end);
        }
    }
};

#endif //SORTING_ALGORITHMS_QUICKSORT_H