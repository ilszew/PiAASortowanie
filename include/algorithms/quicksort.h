#ifndef SORTING_ALGORITHMS_QUICKSORT_H
#define SORTING_ALGORITHMS_QUICKSORT_H
#include <vector>

// quicksort

template <typename T>
class QuickSort
{
public:
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        if (std::distance(start, end) <= 1) return;

        auto quickSort = [&](auto&& self, auto begin, auto end) -> void
        {
            if (std::distance(begin, end) <= 1) return;

            auto pivot = *(end - 1);
            auto i = begin;
            auto j = end - 2;

            while (i <= j)
            {
                while (i <= j && *i < pivot) ++i;
                while (i <= j && *j >= pivot) --j;
                if (i < j) std::iter_swap(i, j);
            }

            std::iter_swap(i, end - 1);
            self(self, begin, i);
            self(self, i + 1, end);
        };

        quickSort(quickSort, start, end);
    }
};
#endif //SORTING_ALGORITHMS_QUICKSORT_H
