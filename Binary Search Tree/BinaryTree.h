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

	BTree<T>* GetLeftTree() {  // 왼쪽 트리의 루트노드 메모리 주소 반환
		return left;
	}

	BTree<T>* GetRightTree() {  // 오른쪽 트리의 루트노드 메모리 주소 반환
		return right;
	}

	void MakeLeftSubTree(BTree<T>* bt) {  // 왼쪽에 서브 트리 연결. 이미 있다면 트리 삭제 및 메모리 소멸 후 연결
		if (left != NULL) {
			size -= left->size;
			DeleteSubTree(left);
		}

		left = bt;
		size += bt->size;
	}

	void MakeRightSubTree(BTree<T>* bt) {  // 오른쪽에 서브 트리 연결. 이미 있다면 트리 삭제 및 메모리 소멸 후 연결
		if (right != NULL) {
			size -= right->size;
			DeleteSubTree(right);
		}

		right = bt;
		size += bt->size;
	}

	BTree<T>* RemoveLeftSubTree() {  // 왼쪽 트리를 제거 후 메모리 소멸
		BTree<T>* delNode = this->left;
		this->left = NULL;

		return delNode;
	}

	BTree<T>* RemoveRightSubTree() {  // 오른쪽 트리를 제거 후 메모리 소멸
		BTree<T>* delNode = this->right;
		this->right = NULL;

		return delNode;
	}

	void ChangeLeftSubTree(BTree<T>* child) { // 메모리 소멸 없이 왼쪽 트리를 child로 변경
		this->left = child;
	}

	void ChangeRightSubTree(BTree<T>* child) { // 메모리 소멸 없이 오른쪽 트리를 child로 변경
		this->right = child;
	}

	void ChangeData(T newData) {  // 노드의 데이터 변경
		data = newData;
	}

	T GetData() {  // 노드 데이터 반환
		return data;
	}

	int BTSize() { // this 포인터 트리의 노드 총 개수
		return size;
	}
};

template <class T>
void DeleteSubTree(BTree<T>* bt) {  // 노드 제거 후 메모리 삭제까지 수행. bt를 루트로 하는 모든 트리 
	if (bt == NULL) return;

	DeleteSubTree(bt->GetLeftTree());
	DeleteSubTree(bt->GetRightTree());
	delete bt;
}

template <class T>
void PreTrav(BTree<T>* nd, void (*action)(T data)) {  // 전위 순회
	if (nd == NULL) return;

	action(nd->GetData());
	PreTrav(nd->GetLeftTree(), action);
	PreTrav(nd->GetRightTree(), action);
}

template <class T>
void InorTrav(BTree<T>* nd, void (*action)(T data)) {  // 중위 순회
	if (nd == NULL) return;

	InorTrav(nd->GetLeftTree(), action);
	action(nd->GetData());
	InorTrav(nd->GetRightTree(), action);
}

template <class T>
void PostTrav(BTree<T>* nd, void (*action)(T data)) {  // 후위 순회
	if (nd == NULL) return;

	PostTrav(nd->GetLeftTree(), action);
	PostTrav(nd->GetRightTree(), action);
	action(nd->GetData());
}

#endif
