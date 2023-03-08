#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <iostream>

using namespace std;


template <class T>
class BTree {
private:
	T data;
	BTree<T>* left;
	BTree<T>* right;
	int size; // 해당 노드를 루트로 하는 Sub Tree의 사이즈
public:
	BTree(T data1) : data(data1), size(1) {
		left = NULL;
		right = NULL;
	}

	BTree<T>* GetLeftTree() {
		return left;
	}

	BTree<T>* GetRightTree() {
		return right;
	}

	void MakeLeftSubTree(BTree<T>* bt) {
		if (left != NULL) {
			size -= left->size;
			DeleteSubTree(left);
		}

		left = bt;
		size += bt->size;
	}

	void MakeRightSubTree(BTree<T>* bt) {
		if (right != NULL) {
			size -= right->size;
			DeleteSubTree(right);
		}

		right = bt;
		size += bt->size;
	}

	BTree<T>* RemoveLeftSubTree() {
		BTree<T>* delNode = this->left;
		this->left = NULL;

		return delNode;
	}

	BTree<T>* RemoveRightSubTree() {
		BTree<T>* delNode = this->right;
		this->right = NULL;

		return delNode;
	}

	void ChangeLeftSubTree(BTree<T>* child) {
		this->left = child;
	}

	void ChangeRightSubTree(BTree<T>* child) {
		this->right = child;
	}

	void ChangeData(T newData) {
		data = newData;
	}

	T GetData() {
		return data;
	}

	int BTSize() {
		return size;
	}

	friend void ChangeLeftSubTree(BTree<T>* parent, BTree<T>* child);
	friend void ChangeRightSubTree(BTree<T>* parent, BTree<T>* child);
};

template <class T>
void DeleteSubTree(BTree<T>* bt) {
	if (bt == NULL) return;

	DeleteSubTree(bt->GetLeftTree());
	DeleteSubTree(bt->GetRightTree());
	delete bt;
}

template <class T>
void PreTrav(BTree<T>* nd, void (*action)(T data)) {
	if (nd == NULL) return;

	action(nd->GetData());
	PreTrav(nd->GetLeftTree(), action);
	PreTrav(nd->GetRightTree(), action);
}

template <class T>
void InorTrav(BTree<T>* nd, void (*action)(T data)) {
	if (nd == NULL) return;

	InorTrav(nd->GetLeftTree(), action);
	action(nd->GetData());
	InorTrav(nd->GetRightTree(), action);
}

template <class T>
void PostTrav(BTree<T>* nd, void (*action)(T data)) {
	if (nd == NULL) return;

	PostTrav(nd->GetLeftTree(), action);
	PostTrav(nd->GetRightTree(), action);
	action(nd->GetData());
}

#endif
