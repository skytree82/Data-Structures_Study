#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <string>
#include "Heap.h"

using namespace std;

template <class T>
class PriorityQueue{
private:
	Heap<T>* heapQueue;
public:
	PriorityQueue(bool (*_cmp)(T senior, T subord)){
		heapQueue = new Heap<T>(_cmp);
	}

	bool PQEmpty() {
		if (heapQueue->HeapEmpty()) return true;
		else return false;
	}

	void PQEnqueue(T data) {
		heapQueue->HeapInsert(data);
	}

	T PQDequeue() {
		return heapQueue->HeapDelete();
	}
};
#endif // !__PRIORITY_QUEUE_H__
