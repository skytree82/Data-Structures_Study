#ifndef __HEAP_H__
#define __HEAP_H__

#include <iostream>

#define MAX 100
#define ParentIdx(idx) idx / 2
#define LeftIdx(idx) idx * 2
#define RightIdx(idx) idx * 2 + 1

template <class T>
class Heap {
private:
	int heapSize;
	T heapArr[MAX];
	bool (*cmp)(T senior, T subord); // senior의 우선순위가 높으면 true
public:
	Heap(bool(*_cmp)(T senior, T subord)) : cmp(_cmp), heapSize(0) {}

	bool HeapEmpty() {
		if (heapSize == 0) return true;
		else return false;
	}

	void HeapInsert(T data) {
		if (heapSize == MAX - 1) {
			std::cout << "Memory Access Error!";
			exit(-1);
		}

		heapSize++;
		int curIdx = heapSize;

		while (curIdx != 1 && !(cmp(heapArr[ParentIdx(curIdx)], data))) {
			heapArr[curIdx] = heapArr[ParentIdx(curIdx)];
			curIdx = ParentIdx(curIdx);
		}

		heapArr[curIdx] = data;
	}

	T HeapDelete() {
		if (this->HeapEmpty()) {
			std::cout << "Memory Access Error!";
			exit(-1);
		}

		T delData = heapArr[1];
		T lastData = heapArr[heapSize];

		int curIdx = 1;
		int childIdx;

		while (childIdx = this->HighPrecChildIdx(curIdx)) {
			if (cmp(lastData, heapArr[childIdx])) break;

			heapArr[curIdx] = heapArr[childIdx];
			curIdx = childIdx;
		}

		heapArr[curIdx] = lastData;
		heapSize--;

		return delData;
	}

	int HighPrecChildIdx(int idx) {
		if (LeftIdx(idx) > heapSize) return 0;
		else if (LeftIdx(idx) == heapSize) return LeftIdx(idx);
		else {
			if (cmp(heapArr[LeftIdx(idx)], heapArr[RightIdx(idx)])) return LeftIdx(idx);
			else return RightIdx(idx);
		}
	}
};


#endif // !__HEAP_H__
