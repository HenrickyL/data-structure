#ifndef UT_PRIORITY_QUEUE_H
#define UT_PRIORITY_QUEUE_H

#include <stdexcept>
namespace EDA{

template<typename T>
class PriorityQueue{
protected:
    T* _array;
    int _length = 20;
    int _heapSize = 0;

    void _alloc(int value);
    T _getMax()const;
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
void PriorityQueue<T>::_alloc(int size){
    try
    {
        _array = new T[size];
    }
    catch(const std::bad_alloc&)
    {
        throw std::runtime_error("Falha na alocação de memória");
    }
}

template<typename T>
T PriorityQueue<T>::_getMax() const{
    if(this->_heapSize > 0)
        return _array[1];
    else
        throw std::runtime_error("Underflow error!");
}

template<typename T>
T PriorityQueue<T>::First() const{
    return _getMax();
}



}


#endif