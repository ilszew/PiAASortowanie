#ifndef SORTING_ALGORITHMS_QUICKSORT_H
#define SORTING_ALGORITHMS_QUICKSORT_H

#include <vector>
#include <algorithm>
#include <iterator>
#include <stack>

template <typename T>
class QuickSort {
private:
    void insertionSort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end) {
        for (auto i = start + 1; i != end; ++i) {
            auto key = *i;
            auto j = i - 1;

            while (j >= start && *j > key) {
                *(j + 1) = *j;
                --j;
            }
            *(j + 1) = key;
        }
    }

    T medianOfThree(T a, T b, T c) {
        if (a < b) {
            if (b < c) return b;
            else if (a < c) return c;
            else return a;
        } else {
            if (a < c) return a;
            else if (b < c) return c;
            else return b;
        }
    }

public:
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end) {
        if (std::distance(start, end) <= 16) {
            insertionSort(start, end);
            return;
        }

        std::stack<std::pair<typename std::vector<T>::iterator, typename std::vector<T>::iterator>> stack;
        stack.push({start, end});

        while (!stack.empty()) {
            auto [begin, last] = stack.top();
            stack.pop();

            if (std::distance(begin, last) <= 16) {
                insertionSort(begin, last);
                continue;
            }

            auto middle = begin + std::distance(begin, last) / 2;
            T pivot = medianOfThree(*begin, *middle, *(last - 1));

            auto partitionLambda = [&](auto b, auto e) {
                auto i = b;
                auto j = e - 1;

                while (true) {
                    while (i < e && *i < pivot) ++i;
                    while (j >= b && *j > pivot) --j;

                    if (i >= j) break;
                    std::iter_swap(i, j);
                    ++i;
                    --j;
                }
                return i;
            };

            auto partitionPoint = partitionLambda(begin, last);

            if (partitionPoint - begin > 1) {
                stack.push({begin, partitionPoint});
            }
            if (last - partitionPoint > 1) {
                stack.push({partitionPoint, last});
            }
        }
    }
};

#endif //SORTING_ALGORITHMS_QUICKSORT_H