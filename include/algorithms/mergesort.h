#ifndef SORTING_ALGORITHMS_MERGESORT_H
#define SORTING_ALGORITHMS_MERGESORT_H
#include <vector>

// sortowanie przez scalanie

template <typename T>
class MergeSort
{
public:
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        auto size = end - start;
        if (size <= 1) return;
        auto mid = start + size / 2;
        sort(start, mid);
        sort(mid, end);

        std::vector<T> temp;
        auto left = start;
        auto right = mid;

        while (left != mid && right != end) {
            if (*left <= *right)
                temp.push_back(*left++);
            else
                temp.push_back(*right++);
        }

        temp.insert(temp.end(), left, mid);
        temp.insert(temp.end(), right, end);
        std::move(temp.begin(), temp.end(), start);

    };
};
#endif //SORTING_ALGORITHMS_MERGESORT_H
