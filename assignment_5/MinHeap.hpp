//
//  MinHeap.hpp
//  A min-heap template class for sorting objects.
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

    void push(const T& node)
    {
        heap.push_back(node);
        std::push_heap(heap.begin(), heap.end(), MinHeap::compare);
    }

    T& min_pop(void)
    {
        std::pop_heap(heap.begin(), heap.end(), MinHeap::compare);
        T& n = heap.back();
        heap.pop_back();
        return n;
    }
    
    void unheap(void) { std::sort_heap(heap.begin(), heap.end(), MinHeap::compare);}
    void reheap(void) { std::make_heap(heap.begin(), heap.end(), MinHeap::compare);}
    
    void clear(void) { heap.clear(); }
    
    typename std::vector<T>::iterator begin() noexcept { return heap.begin(); }
    typename std::vector<T>::iterator end() noexcept { return heap.end(); }

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
