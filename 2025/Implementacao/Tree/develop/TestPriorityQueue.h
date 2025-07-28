#ifndef TEST_PRIORITY_QUEUE_H
#define TEST_PRIORITY_QUEUE_H


#include "../include/PriorityQueue.h"
#include<iostream>


class TestPriorityQueue {
public:
	static void test() {
		PriorityQueue<int> queue;

		queue.push(4);
		queue.push(5);
		queue.push(2);
		queue.push(5);
		queue.push(1);
		queue.push(3);
		queue.push(2);
		queue.push(9);
		queue.push(6);


		std::cout << "Size: " << queue.size() << std::endl;
		while (!queue.empty()) {
			std::cout << "Top: " << queue.top() << std::endl;
			queue.pop();
		}
	}
};

#endif // !TEST_PRIORITY_QUEUE_H
