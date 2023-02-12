#ifndef __STACK_H__
#define __STACK_H__

#include <vector>

template <class T>

class stack {
private:
	int top;
	std::vector<T> stackArr;
public:
	stack(): top(-1) {}

	void push(T data) {
		stackArr.push_back(data);
		top++;
	}

	bool isempty() {
		if (top == -1) return true;
		else return false;
	}

	T peak() {
		if (this->isempty()) {
			std::cout << "Memory access error!";
			exit(1);
		}
		return stackArr[top];
	}

	T pop() {
		if (this->isempty()) {
			std::cout << "Memory access error!";
			exit(1);
		}
		else {
			return stackArr[top--];
		}
	}

	int size() {
		return top + 1;
	}
};

#endif
