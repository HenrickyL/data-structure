#ifndef PRIORITY_QUEUE_IMP_H
#define PRIORITY_QUEUE_IMP_H

#include"../include/PriorityQueue.h"
#include <stdexcept>

template<typename T, typename Compare>
bool PriorityQueue<T, Compare>::empty() const {
	return heap.empty();
}

template<typename T, typename Compare>
size_t PriorityQueue<T, Compare>::size() const {
	return heap.size();
}


template<typename T, typename Compare>
void PriorityQueue<T, Compare>::push(const T& item) {
	heap.push_back(std::make_shared<T>(item));
	heapifyUp(heap.size() - 1);
}


template<typename T, typename Compare>
void PriorityQueue<T, Compare>::pop() {
	if (empty()) throw std::out_of_range("heap is empty");
	size_t size = this->size();
	std::swap(heap[0], heap[size - 1]);
	heap.pop_back();
	if (!empty())
		heapifyDown(0);
}



template<typename T, typename Compare>
void PriorityQueue<T, Compare>::heapifyUp(size_t index) {
	while (index > 0) {
		size_t parent = (index - 1) / 2;

		if (comp(*heap[index], *heap[parent])) {
			std::swap(heap[index], heap[parent]);
			index = parent;
		}
		else {
			break;
		}
	}
}


template<typename T, typename Compare>
void PriorityQueue<T, Compare>::heapifyDown(size_t index) {
	size_t size = heap.size();
	while (true) {
		size_t left = 2*index + 1;
		size_t right = 2*index + 2;
		size_t best = index;

		if (left < size && comp(*heap[left], *heap[best])) {
			best = left;
		}
		if(right < size && comp(*heap[right], *heap[best])) {
			best = right;
		}

		if (best != index) {
			std::swap(heap[index], heap[best]);
			index = best;
		}
		else {
			break;
		}
	}
}


template<typename T, typename Compare>
T& PriorityQueue<T, Compare>::top() const{
	if (empty())
		throw std::out_of_range("Heap is empty");
	return *heap[0];
}


#endif // !PRIORITY_QUEUE_IMP_H
