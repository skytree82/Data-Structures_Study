#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#include <iostream>
#include "BinaryTree.h"

using namespace std;

template <class T>
void Print(T data) {
	cout << data << ' ';
}

template <class T>
class BSTree {
private:
	BTree<T>* bst;
public:
	BSTree(){
		bst = NULL;
	};

	void BSTInsert(T data) {
		if (bst == NULL) {            // 루트 노드로 저장되어야 하면
			bst = new BTree<T>(data);
			return;
		}

		BTree<T>* curNode = bst;
		BTree<T>* newNode = new BTree<T>(data);

		while (true) {
			if (data == curNode->GetData()) {   // 데이터가 중복되면
				delete newNode;
				return;
			}
			else if (data < curNode->GetData()) {
				if (curNode->GetLeftTree() == NULL) {  // 데이터 추가 자리가 나오면
					curNode->MakeLeftSubTree(newNode);
					return;
				}
				curNode = curNode->GetLeftTree();
			}
			else {
				if (curNode->GetRightTree() == NULL) {
					curNode->MakeRightSubTree(newNode);
					return;
				}
				curNode = curNode->GetRightTree();
			}
		}
	}

	BTree<T>* BSTSearch(T target) {
		BTree<T>* curNode = bst;
		T curData;

		while (curNode) { // curNode가 NULL이 아닐 때까지
			curData = curNode->GetData();

			if (target == curData) {
				return curNode;
			}
			else if (target < curData) {
				curNode = curNode->GetLeftTree();
			}
			else {
				curNode = curNode->GetRightTree();
			}
		}
		return NULL;
	}

	BTree<T>* BSTRemove(T target) {
		BTree<T>* parentVirtualNode = new BTree<T>(target);
		BTree<T>* parentNode = parentVirtualNode;
		BTree<T>* delNode = NULL;
		BTree<T>* curNode = bst;

		parentVirtualNode->ChangeRightSubTree(bst);

		while (curNode) { // curNode가 NULL이 아닐 때까지
			if (target == curNode->GetData()) {
				delNode = curNode;
				break;
			}
			else if (target < curNode->GetData()) {
				parentNode = curNode;
				curNode = curNode->GetLeftTree();
			}
			else {
				parentNode = curNode;
				curNode = curNode->GetRightTree();
			}
		}

		if (curNode == NULL) return NULL;

		if (delNode->GetLeftTree() == NULL && delNode->GetRightTree() == NULL) { // 삭제 대상이 단말노드
			if (parentNode->GetLeftTree() == delNode) // 삭제 대상이 왼쪽 노드면
				parentNode->RemoveLeftSubTree(); // 왼쪽 노드 제거
			else
				parentNode->RemoveRightSubTree(); // 오른쪽 노드 제거
		}

		else if (delNode->GetLeftTree() == NULL || delNode->GetRightTree() == NULL) { // 삭제 대상이 한 개의 자식노드 포함
			BTree<T>* delChildNode; // 삭제 대상의 자식 트리 루트 노드

			// 삭제 대상의 자식 트리 찾기
			if (delNode->GetLeftTree()) {
				delChildNode = delNode->GetLeftTree();
			}
			else {
				delChildNode = delNode->GetRightTree();
			}

			//삭제 대상의 자식 트리와 삭제 대상의 부모 트리 연결
			if (parentNode->GetLeftTree() == delNode) {
				parentNode->ChangeLeftSubTree(delChildNode);
			}
			else {
				parentNode->ChangeRightSubTree(delChildNode);
			}
		}

		else { // 삭제 대상이 두 개의 자식노드 포함
			BTree<T>* alterNode = delNode->GetRightTree(); // 대체노드 (오른쪽 트리의 최솟값) -> 최솟값이므로 왼쪽 트리는 항상 NULL
			BTree<T>* alterParentNode = delNode;
			T delData;

			while (alterNode->GetLeftTree()) {
				alterParentNode = alterNode;
				alterNode = alterNode->GetLeftTree();
			}

			delData = delNode->GetData(); // 데이터 백업
			delNode->ChangeData(alterNode->GetData()); // 삭제 노드에 대체 노드 대입

			if (alterParentNode->GetLeftTree() == alterNode) { // 대체 노드가 왼쪽 자식 노드면
				alterParentNode->ChangeLeftSubTree(alterNode->GetRightTree()); // 대체 노드의 오른쪽 트리를 대체 노드 부모 왼쪽에 연결
			}
			else {
				alterParentNode->ChangeRightSubTree(alterNode->GetRightTree());// 대체 노드의 오른쪽 트리를 대체 노드 부모 오른쪽에 연결
			}

			delNode = alterNode; // 대체되어 빠진 노드는 제거
			delNode->ChangeData(delData); // 빠진 노드에 백업된 제거 데이터 대입
		}

		if (parentVirtualNode->GetRightTree() != bst) { // 루트 노드가 변경되었다면
			bst = parentVirtualNode->GetRightTree(); // 루트 노드 재설정
		}

		delete parentVirtualNode;
		return delNode;
	}

	void PrintData() {
		InorTrav(bst, Print); // 중위순회 데이터 출력 (오름차순)
	}
};



#endif // !__BINARY_SEARCH_TREE_H__
