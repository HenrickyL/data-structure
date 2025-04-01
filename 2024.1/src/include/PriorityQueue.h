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
    bool _isMaxHeap; // True para Max Heap, False para Min Heap

    void _alloc(int value);
    void _fixUp(int i); // Método genérico para ajustar a heap (Max/Min)
    void _fixDown(int i); // Método para mover o elemento para baixo
    void _increaseKey(int i, T newValue); // Usado para Heap de Max
    void _decreaseKey(int i, T newValue); // Usado para Heap de Min
    bool _compare(T a, T b) const; // Comparação genérica para Max/Min
    T _getExtremum() const; // Retorna o maior (ou menor) elemento da heap

public:
    PriorityQueue(bool isMaxHeap = true);
    ~PriorityQueue();

    T Dequeue();
    void Enqueue(T value);
    T First() const;
    void Print() const;
};


template<typename T>
PriorityQueue<T>::PriorityQueue(bool isMaxHeap) : _length(20), _heapSize(0), _isMaxHeap(isMaxHeap) {
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

// Comparação genérica para Max ou Min Heap
template<typename T>
bool PriorityQueue<T>::_compare(T a, T b) const {
    if (_isMaxHeap)
        return a >= b; // Max Heap
    else
        return a <= b; // Min Heap
}

// Função para obter o maior (ou menor) elemento
template<typename T>
T PriorityQueue<T>::_getExtremum() const {
    if (_heapSize > 0)
        return _array[1];
    else
        throw std::runtime_error("Underflow error!");
}

// Método genérico para ajustar a heap após inserção (sobe o elemento)
template<typename T>
void PriorityQueue<T>::_fixUp(int i) {
    int p = i / 2;
    T aux;
    while (p >= 1 && _compare(_array[i], _array[p])) {
        // Troca
        aux = _array[i];
        _array[i] = _array[p];
        _array[p] = aux;
        i = p;
        p = p / 2;
    }
}

// Método genérico para ajustar a heap após remoção (desce o elemento)
template<typename T>
void PriorityQueue<T>::_fixDown(int i) {
    int left = 2 * i;
    int right = 2 * i + 1;
    int p = i;
    int minChild = p;

    //exist left
    if (left <= _heapSize)
        if( _compare(_array[left], _array[minChild]))
            minChild = left;
    //exist right
    if (right <= _heapSize)
        if( _compare(_array[right], _array[minChild])) // or p or left
            minChild = right;

    //change
    if (minChild != i) {
        T aux = _array[i];
        _array[i] = _array[minChild];
        _array[minChild] = aux;
        _fixDown(minChild);
    }
}

// Aumenta o valor da chave em uma Max Heap
template<typename T>
void PriorityQueue<T>::_increaseKey(int i, T newValue) {
    if (newValue < _array[i]) {
        throw std::runtime_error("Invalid Key!");
    }
    _array[i] = newValue;
    this->_isMaxHeap ?_fixUp(i) : _fixDown(i);
}

// Diminui o valor da chave em uma Min Heap
template<typename T>
void PriorityQueue<T>::_decreaseKey(int i, T newValue) {
    if (newValue > _array[i]) {
        throw std::runtime_error("Invalid Key!");
    }
    _array[i] = newValue;
    this->_isMaxHeap ?_fixDown(i) : _fixUp(i);
}

// Método Enqueue para inserir novos valores na heap
template<typename T>
void PriorityQueue<T>::Enqueue(T value) {
    if (_heapSize >= _length - 1) {
        throw std::runtime_error("Heap overflow");
    }
    _heapSize++;
    _array[_heapSize] = value;
    _fixUp(_heapSize);
}

// Método Dequeue para remover o maior (ou menor) valor da heap
template<typename T>
T PriorityQueue<T>::Dequeue() {
    if (_heapSize < 1) {
        throw std::runtime_error("Underflow error!");
    }
    T extremum = _array[1];
    _array[1] = _array[_heapSize];
    _heapSize--;
    _fixDown(1); // Reajusta a heap
    return extremum;
}

// Método First para acessar o maior (ou menor) valor da heap
template<typename T>
T PriorityQueue<T>::First() const {
    return _getExtremum();
}
template<typename T>
void  PriorityQueue<T>::Print() const{
    for(int i=1; i<=this->_heapSize; i++){
    std::cout << _array[i] << " ,";
    }
    std::cout << std::endl;
}



}// namespace EDA


#endif