#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <iostream>

template <class T>
struct Node {
	T data;
	Node<T>* prev;
	Node<T>* next;
};

template <class T>
class Queue {
private:
	Node<T>* head;
	Node<T>* tail;
	int size;
public:
	Queue(): size(0) {
		head = NULL;
		tail = NULL;
	}

	bool QEmpty() {
		if (size == 0) return true;
		else return false;
	}

	void QPush(T data) {
		Node<T>* newNode = new Node<T>;
		newNode->data = data;

		if (this->QEmpty()) {
			head = newNode;
			tail = newNode;
			newNode->next = NULL;
			newNode->prev = NULL;
		}
		else {
			newNode->prev = tail;
			newNode->next = NULL;
			tail->next = newNode;
			tail = newNode;
		}

		size++;
	}

	T QPop() {
		if (this->QEmpty()) {
			std::cout << "Memory Access Error!";
			exit(-1);
		}

		Node<T>* delNode = head;
		T delData = delNode->data;

		if (size == 1) {
			head = NULL;
			tail = NULL;
		}
		else {
			head->next->prev = NULL;
			head = head->next;
		}

		size--;
		delete delNode;
		return delData;
	}

	T QFront() {
		if (this->QEmpty()) {
			std::cout << "Memory Access Error!";
			exit(-1);
		}

		return head->data;
	}

	T QBack() {
		if (this->QEmpty()) {
			std::cout << "Memory Access Error!";
			exit(-1);
		}

		return tail->data;
	}

	int QSize() {
		return size;
	}
};

#endif
