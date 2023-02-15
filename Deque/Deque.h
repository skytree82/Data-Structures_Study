#ifndef __DEQUE_H__
#define __DEQUE_H__

#include <iostream>

template <class T>
struct Node {
	T data;
	struct Node<T>* prev;
	struct Node<T>* next;
};

template <class T>
class Deque {
private:
	Node<T>* head;
	Node<T>* tail;
	int size;
public:
	Deque() : size(0) {
		head = NULL;
		tail = NULL;
	}

	bool DQEmpty() {
		if (size == 0) return true;
		else return false;
	}

	void DQPush_Front(T data) {
		Node<T>* newNode = new Node<T>;
		newNode->data = data;

		if (this->DQEmpty()) {
			head = newNode;
			tail = newNode;
			newNode->prev = NULL;
			newNode->next = NULL;
		}
		else {
			newNode->next = head;
			newNode->prev = NULL;
			head->prev = newNode;
			head = newNode;
		}

		size++;
	}

	void DQPush_Back(T data) {
		Node<T>* newNode = new Node<T>;
		newNode->data = data;

		if (this->DQEmpty()) {
			head = newNode;
			tail = newNode;
			newNode->prev = NULL;
			newNode->next = NULL;
		}
		else {
			newNode->next = NULL;
			newNode->prev = tail;
			tail->next = newNode;
			tail = newNode;
		}

		size++;
	}

	T DQPop_Front() {
		if (this->DQEmpty()) {
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
			size--;
		}

		delete delNode;
		return delData;
	}

	T DQPop_Back() {
		if (this->DQEmpty()) {
			std::cout << "Memory Access Error!";
			exit(-1);
		}
		Node<T>* delNode = tail;
		T delData = delNode->data;
		if (size == 1) {
			head == NULL;
			tail == NULL;
		}
		else {
			tail->prev->next = NULL;
			tail = tail->prev;
			size--;
		}

		delete delNode;
		return delData;
	}

	T DQFront() {
		if (this->DQEmpty()) {
			std::cout << "Memory Access Error!";
			exit(-1);
		}

		return head->data;
	}

	T DQBack() {
		if (this->DQEmpty()) {
			std::cout << "Memory Access Error!";
			exit(-1);
		}

		return tail->data;
	}

	int DQSize() {
		return size;
	}
};

#endif
