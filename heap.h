#ifndef Revi_heap_header_def
#define Revi_heap_header_def

#include <vector>
#include <functional>

template<typename Tp, typename Sequence = std::vector<Tp>,
        typename Compare = std::less<typename  Sequence::value_type>>
class Heap{

public:
    typedef typename	Sequence::value_type        value_type;
    typedef typename	Sequence::reference         reference;
    typedef typename	Sequence::const_reference   const_reference;
    typedef typename    Sequence::size_type         size_type;
    typedef             Sequence                    container_type;
    typedef             Compare                     value_compare;

protected:
    std::vector<Tp> heap;

public:
    Heap() {}

    Heap(std::vector<Tp> seq, bool heaped = false) : heap(seq){
        if(!heaped){
            for (size_type i = heap.size() / 2 - 1; i >= 0 ; --i) {
                heapify(i);
            }
        }
    }

    void heapify(size_type i){
        value_type x = heap[i];
        while(i * 2 + 1 < heap.size()) {
            size_type c1 = i * 2 + 1;
            if (c1 >= heap.size()) return;

            if (c1 + 1 < heap.size() && value_compare ()(heap[c1], heap[c1 + 1])) c1++;

            if (value_compare ()(heap[c1], heap[i])) break;
            heap[i] = heap[c1];
            i = c1;
        }
        heap[i] = x;
    }

    [[nodiscard]] bool empty() const{
        return heap.empty();
    }

    size_type size() const{
        return heap.size();
    }

    value_type top() const{
        if(!heap.empty()) return heap.front();
        else return 0;
    }

    value_type pop(){
        if(heap.empty()) return 0;
        value_type t = heap[0];
        value_type x = heap.back();
        heap.pop_back();
        size_type i = 0;
        while(i * 2 + 1 < heap.size()){
            size_type c1 = i * 2 + 1, c2 = c1 + 1;
            if(value_compare () (heap[c1], heap[c2]))
                c1 = c2;
            if(value_compare ()(heap[c1], x)) break;
            heap[i] = heap[c1];
            i = c1;
        }
        heap[i] = x;
        return t;
    }

    void push(Tp x){
        heap.push_back(x);
        size_type i = heap.size() - 1;
        while(i > 0){
            size_type p = (i - 1) / 2;
            if(value_compare ()(x, heap[p])) break;
            heap[i] = heap[p];
            i = p;
        }
        heap[i] = x;
    }
};

#endif