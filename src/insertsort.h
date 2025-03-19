#ifndef SORTING_ALGORITHMS_INSERTSORT_H
#define SORTING_ALGORITHMS_INSERTSORT_H
#include <vector>

// sortowanie przez wstawianie

template <typename T>
class InsertSort
{
public:
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        for (auto it = start + 1; it != end; ++it)
        {
            T key = *it;
            auto j = it;
            while (j > start && *(j - 1) > key)
                *(j--) = *(j - 1);
            *j = key;
        }
    };
};

#endif //SORTING_ALGORITHMS_INSERTSORT_H
