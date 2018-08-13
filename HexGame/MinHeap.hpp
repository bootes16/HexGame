//
//  MinHeap.hpp
//  A template class for a min-heap based on the std::vector<> and
//  std::make_heap() functionality. Purpose it to wrap the standard library
//  functionality into a cleaner interface.
//
//  Created by Greg on 2018-06-11.
//  Copyright © 2018 Greg. All rights reserved.
//

#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include <vector>
#include <algorithm>

template <class T>
class MinHeap
{
public:
    MinHeap() {}
    ~MinHeap() { heap.clear(); }
    
    // Prevent compiler from auto-generating stuff we don't want.
    MinHeap(const MinHeap& heap)                = delete;
    MinHeap(MinHeap&& heap)                     = delete;
    MinHeap& operator= (const MinHeap& heap)    = delete;
    MinHeap& operator= (MinHeap&& heap)         = delete;
    
    // Push an object onto the heap and sort the heap.
    void push(const T& node)
    {
        heap.push_back(node);
        std::push_heap(heap.begin(), heap.end(), MinHeap::compare);
    }

    // Pop and return the smallest object from the sorted heap.
    T& min_pop(void)
    {
        std::pop_heap(heap.begin(), heap.end(), MinHeap::compare);
        T& n = heap.back();
        heap.pop_back();
        return n;
    }
    
    // Clear the min-heap of contents.
    void clear(void) { heap.clear(); }
    
    // Allow for ability to modify heap objects in-place in heap.
    // The heap gets corrupted if values are changed. To iterates and
    // modify, first 'unheap()' the heap, interate and change, then 'reheap()'.
    void unheap(void) { std::sort_heap(heap.begin(), heap.end(), MinHeap::compare);}
    void reheap(void) { std::make_heap(heap.begin(), heap.end(), MinHeap::compare);}
    
    typename std::vector<T>::iterator begin() noexcept { return heap.begin(); }
    typename std::vector<T>::iterator end() noexcept { return heap.end(); }

    // Use operator> for the object type T for compare.
    static bool compare(const T& lhs, const T& rhs) { return lhs > rhs; }

    unsigned size(void) { return heap.size(); }
    
    void dbg_print_heap(void) {
        for (auto& t : heap)
            std::cout << t << " ";
        std::cout << endl;
    }

private:
    std::vector<T> heap;
};

#endif /* MINHEAP_HPP */
