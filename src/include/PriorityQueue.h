#ifndef UT_PRIORITY_QUEUE_H
#define UT_PRIORITY_QUEUE_H

#include <stdexcept>
namespace EDA{

template<typename T>
class PriorityQueue{
protected:
    int* _array;
    int _length = 20;
    int _heapSize = 0;

    void _alloc(int value);
public:
    PriorityQueue();
    ~PriorityQueue();

    T Dequeue();
    void Enqueue(int key,T value);
    T First() const;
};


template<typename T>
PriorityQueue<T>::PriorityQueue() : _length(20), _heapSize(0){
    _alloc(_length);
}

template<typename T>
PriorityQueue<T>::~PriorityQueue(){
    delete[] _array;
}


template<typename T>
void PriorityQueue<T>::_alloc(int value){
    try
    {
        _array = new int[value];
    }
    catch(const std::bad_alloc&)
    {
        throw std::runtime_error("Falha na alocação de memória");
    }
}

}


#endif