#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <functional>
#include<vector>
#include <memory>

template<typename T, typename Compare = std::less<T>>
class PriorityQueue {
private:
	std::vector<std::shared_ptr<T>> heap;
	Compare comp;
public:
	void push(const T& item);
	void pop();
	T& top() const; 
	bool empty()const;
	size_t size() const;

private:
	void heapifyDown(size_t index);
	void heapifyUp(size_t index);
};

#include "../src/PriorityQueue.impl.h"
#endif