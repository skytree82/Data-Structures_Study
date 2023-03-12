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
protected:
	BTree<T>* bst;
public:
	BSTree(){
		bst = NULL;
	};

	void BSTInsert(T data) {
		if (bst == NULL) {            // ��Ʈ ���� ����Ǿ�� �ϸ�
			bst = new BTree<T>(data);
			return;
		}

		BTree<T>* curNode = bst;
		BTree<T>* newNode = new BTree<T>(data);

		while (true) {
			if (data == curNode->GetData()) {   // �����Ͱ� �ߺ��Ǹ�
				delete newNode;
				return;
			}
			else if (data < curNode->GetData()) {
				if (curNode->GetLeftTree() == NULL) {  // ������ �߰� �ڸ��� ������
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

		while (curNode) { // curNode�� NULL�� �ƴ� ������
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

		while (curNode) { // curNode�� NULL�� �ƴ� ������
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

		if (delNode->GetLeftTree() == NULL && delNode->GetRightTree() == NULL) { // ���� ����� �ܸ����
			if (parentNode->GetLeftTree() == delNode) // ���� ����� ���� ����
				parentNode->RemoveLeftSubTree(); // ���� ��� ����
			else
				parentNode->RemoveRightSubTree(); // ������ ��� ����
		}

		if (delNode->GetLeftTree() == NULL || delNode->GetRightTree() == NULL) { // ���� ����� �� ���� �ڽĳ�� ����
			BTree<T>* delChildNode; // ���� ����� �ڽ� Ʈ�� ��Ʈ ���

			// ���� ����� �ڽ� Ʈ�� ã��
			if (delNode->GetLeftTree()) {
				delChildNode = delNode->GetLeftTree();
			}
			else {
				delChildNode = delNode->GetRightTree();
			}

			//���� ����� �ڽ� Ʈ���� ���� ����� �θ� Ʈ�� ����
			if (parentNode->GetLeftTree() == delNode) {
				parentNode->ChangeLeftSubTree(delChildNode);
			}
			else {
				parentNode->ChangeRightSubTree(delChildNode);
			}
		}

		else { // ���� ����� �� ���� �ڽĳ�� ����
			BTree<T>* alterNode = delNode->GetRightTree(); // ��ü��� (������ Ʈ���� �ּڰ�) -> �ּڰ��̹Ƿ� ���� Ʈ���� �׻� NULL
			BTree<T>* alterParentNode = delNode;
			T delData;

			while (alterNode->GetLeftTree()) {
				alterParentNode = alterNode;
				alterNode = alterNode->GetLeftTree();
			}

			delData = delNode->GetData(); // ������ ���
			delNode->ChangeData(alterNode->GetData()); // ���� ��忡 ��ü ��� ����

			if (alterParentNode->GetLeftTree() == alterNode) { // ��ü ��尡 ���� �ڽ� ����
				alterParentNode->ChangeLeftSubTree(alterNode->GetRightTree()); // ��ü ����� ������ Ʈ���� ��ü ��� �θ� ���ʿ� ����
			}
			else {
				alterParentNode->ChangeRightSubTree(alterNode->GetRightTree());// ��ü ����� ������ Ʈ���� ��ü ��� �θ� �����ʿ� ����
			}

			delNode = alterNode; // ��ü�Ǿ� ���� ���� ����
			delNode->ChangeData(delData); // ���� ��忡 ����� ���� ������ ����
		}

		if (parentVirtualNode->GetRightTree() != bst) { // ��Ʈ ��尡 ����Ǿ��ٸ�
			bst = parentVirtualNode->GetRightTree(); // ��Ʈ ��� �缳��
		}

		delete parentVirtualNode;
		return delNode;
	}

	void PrintData() {
		InorTrav(bst, Print); // ������ȸ ������ ��� (��������)
	}
};


#endif // !__BINARY_SEARCH_TREE_H__
