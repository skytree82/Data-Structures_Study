#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include <iostream>
#include <stack>
#include "BinarySearchTree.h"

using namespace std;

template <class T>
class AVLTree : public BSTree<T> {
private:
	BTree<T>*& avlt;
public:
	AVLTree() : avlt(BSTree<T>::bst) {}

	void AVLTInsert(T data) {
		if (avlt == NULL) {
			avlt = new BTree<T>(data);
			return;
		}
		BTree<T>* curNode = avlt;
		BTree<T>* newNode = new BTree<T>(data);
		stack<BTree<T>*> parentNodes;  // 데이터를 추가하는 과정에서 지나간 노드들

		while (true) {
			if (data == curNode->GetData()) {   // 데이터가 중복되면
				delete newNode;
				return;
			}
			else if (data < curNode->GetData()) {
				parentNodes.push(curNode);
				if (curNode->GetLeftTree() == NULL) {  // 데이터 추가 자리가 나오면
					curNode->MakeLeftSubTree(newNode);
					break;
				}
				curNode = curNode->GetLeftTree();
			}
			else {
				parentNodes.push(curNode);
				if (curNode->GetRightTree() == NULL) {
					curNode->MakeRightSubTree(newNode);
					break;
				}
				curNode = curNode->GetRightTree();
			}
		}
		
		while (!parentNodes.empty()) {
			BTree<T>*& node = parentNodes.top();
			parentNodes.pop();
			node = Rebalance(node);
		}
	}

	BTree<T>* AVLTRemove(T target) {
		BTree<T>* parentVirtualNode = new BTree<T>(target);
		BTree<T>* parentNode = parentVirtualNode;
		BTree<T>* delNode = NULL;
		BTree<T>* curNode = avlt;

		parentVirtualNode->ChangeRightSubTree(avlt);

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

		if (parentVirtualNode->GetRightTree() != avlt) { // 루트 노드가 변경되었다면
			avlt = parentVirtualNode->GetRightTree(); // 루트 노드 재설정
		}

		Rebalance(avlt);
		delete parentVirtualNode;
		return delNode;
	}
};

template <class T>
BTree<T>*& Rebalance(BTree<T>*& bst) {
	int unbalFactor = GetUnbalFactor(bst);

	if (unbalFactor > 1) { // LX 계열 상황이면
		if (GetUnbalFactor(bst->GetLeftTree()) > 0) { // LL상태이면
			bst = LLRotate(bst);
		}
		else  // LR 상태이면
			bst = LRRotate(bst);
	}
	else if (unbalFactor < -1) { // RX 계열 상황이면
		if (GetUnbalFactor(bst->GetRightTree()) < 0) { // RR상태이면
			bst = RRRotate(bst);
		}
		else // RL상태이면
			bst = RLRotate(bst);
	}

	return bst;
}

template <class T>
BTree<T>* LLRotate(BTree<T>* bst) {
	BTree<T>* pNode = bst;
	BTree<T>* cNode = bst->GetLeftTree();

	T tmp = pNode->GetData();			// 부모노드 자식노드 데이터 교환
	pNode->ChangeData(cNode->GetData());
	cNode->ChangeData(tmp);

	pNode->ChangeLeftSubTree(cNode->GetLeftTree());  // pNode가 루트 노드가 되도록 유지하면서 회전
	cNode->ChangeLeftSubTree(cNode->GetRightTree());
	cNode->ChangeRightSubTree(pNode->GetRightTree());
	pNode->ChangeRightSubTree(cNode);
	return pNode;
}

template <class T>
BTree<T>* RRRotate(BTree<T>* bst) {
	BTree<T>* pNode = bst;
	BTree<T>* cNode = bst->GetRightTree();

	T tmp = pNode->GetData();			// 부모노드 자식노드 데이터 교환
	pNode->ChangeData(cNode->GetData());
	cNode->ChangeData(tmp);

	pNode->ChangeRightSubTree(cNode->GetRightTree());  // pNode가 루트 노드가 되도록 유지하면서 회전
	cNode->ChangeRightSubTree(cNode->GetLeftTree());
	cNode->ChangeLeftSubTree(pNode->GetLeftTree());
	pNode->ChangeLeftSubTree(cNode);
	return pNode;
}

template <class T>
BTree<T>* LRRotate(BTree<T>* bst) {
	BTree<T>* pNode = bst;
	BTree<T>* cNode = bst->GetLeftTree();

	pNode->ChangeLeftSubTree(RRRotate(cNode));  // 자식노드 RR회전 후
	return LLRotate(pNode);  // 전반적 LL회전
}

template <class T>
BTree<T>* RLRotate(BTree<T>* bst) {
	BTree<T>* pNode = bst;
	BTree<T>* cNode = bst->GetRightTree();

	pNode->ChangeRightSubTree(LLRotate(cNode));  // 자식 노드 LL회전 후
	return RRRotate(pNode);  // 전반적 RR
}

template <class T>
int GetUnbalFactor(BTree<T>* bst) {
	int leftHeight = GetHeight(bst->GetLeftTree());
	int rightHeight = GetHeight(bst->GetRightTree());

	return leftHeight - rightHeight;
}

#endif // !__AVL_TREE_H__
