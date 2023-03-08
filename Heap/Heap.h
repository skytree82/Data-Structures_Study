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
	T heapArr[MAX]; // 배열 기반 힙. 인덱스는 1부터 시작 -> 힙 사이즈 == 힙 최하단 노드 
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

		while (curIdx != 1 && !(cmp(heapArr[ParentIdx(curIdx)], data))) {  // 인덱스가 1(top of heap)이 아니거나 parent node보다 우선순위가 높다면
			heapArr[curIdx] = heapArr[ParentIdx(curIdx)];  // parent node를 curIdx에 대입하여 하나씩 밀기
			curIdx = ParentIdx(curIdx);
		}

		heapArr[curIdx] = data; // 
	}

	T HeapDelete() {
		if (this->HeapEmpty()) {
			std::cout << "Memory Access Error!";
			exit(-1);
		}

		T delData = heapArr[1]; // 힙의 최상단 데이터를 제거
		T lastData = heapArr[heapSize];

		int curIdx = 1;
		int childIdx;

		while (childIdx = this->HighPrecChildIdx(curIdx)) {  // 자식 노드가 더 없을 때까지 반복. childIdx는 자식 노드 중 가장 높은 우선순위 받음.
			if (cmp(lastData, heapArr[childIdx])) break;  // 우선순위 조건 만족하면 반복 중단

			heapArr[curIdx] = heapArr[childIdx];
			curIdx = childIdx;
		}

		heapArr[curIdx] = lastData;
		heapSize--;

		return delData;
	}

	int HighPrecChildIdx(int idx) {  // idx 자식 노드 중 우선순위가 가장 높은 노드 인덱스 반환
		if (LeftIdx(idx) > heapSize) return 0; // 힙 사이즈보다 leftIdx가 큼 -> 힙 사이즈 초과, 자식 노드 없음.
		else if (LeftIdx(idx) == heapSize) return LeftIdx(idx);  // leftIdx가 힙 사이즈 -> 자식 노드가 leftIdx밖에 없음.
		else {  // 자식 노드가 둘이면
			if (cmp(heapArr[LeftIdx(idx)], heapArr[RightIdx(idx)])) return LeftIdx(idx);  // 자식 노드들 중 우선순위 높은 자식 노드 인덱스 반환
			else return RightIdx(idx);
		}
	}
};


#endif // !__HEAP_H__
