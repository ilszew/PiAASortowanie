#ifndef SORTING_ALGORITHMS_HEAPSORT_H
#define SORTING_ALGORITHMS_HEAPSORT_H

#include <vector>

template <typename T>
class Heap
{
public:
    Heap(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        data.push_back(T()); // element pusty dla indeksowania od 1
        for (auto it = start; it != end; ++it)
            data.push_back(*it);
        heapSize = data.size() - 1;
        buildHeap();
    }

    void removeMax()
    {
        if (heapSize < 1) return;
        std::swap(data[1], data[heapSize]);
        heapSize--;
        heapify(1);
    }

    std::size_t size()
    {
        return heapSize;
    }

    bool empty()
    {
        return heapSize == 0;
    }

    T& operator[](int index)
    {
        return data[index];
    }

private:
    std::vector<T> data;
    std::size_t heapSize;

    void buildHeap()
    {
        for (int i = heapSize / 2; i >= 1; --i)
            heapify(i);
    }

    void heapify(int i)
    {
        int left = 2 * i;
        int right = 2 * i + 1;
        int largest = i;

        if (left <= heapSize && data[left] > data[largest])
            largest = left;
        if (right <= heapSize && data[right] > data[largest])
            largest = right;

        if (largest != i)
        {
            std::swap(data[i], data[largest]);
            heapify(largest);
        }
    }
};


// sortowanie przez kopcowanie

template <typename T>
class HeapSort
{
public:
    void sort(typename std::vector<T>::iterator start, typename std::vector<T>::iterator end)
    {
        Heap<T> heap(start, end);
        auto it = end;
        while (!heap.empty())
        {
            --it;
            *it = heap[1];  // największy element
            heap.removeMax();
        }
    };
};

#endif //SORTING_ALGORITHMS_HEAPSORT_H