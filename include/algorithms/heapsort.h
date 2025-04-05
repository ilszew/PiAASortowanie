#ifndef SORTING_ALGORITHMS_HEAPSORT_H
#define SORTING_ALGORITHMS_HEAPSORT_H

#include <vector>
#include <queue>

template <typename T>
class HeapSort {
public:
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end) {
        std::priority_queue<T> maxHeap(start, end);

        auto it = end;
        while (!maxHeap.empty()) {
            --it;
            *it = maxHeap.top();
            maxHeap.pop();
        }
    }
};

#endif //SORTING_ALGORITHMS_HEAPSORT_H