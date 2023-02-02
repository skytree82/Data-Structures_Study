#ifndef __D_LINKED_LIST_H__
#define __D_LINKED_LIST_H__

template <class T>
struct Node {
    T data;
    struct Node* prev;
    struct Node* next;
};

template <class T>
class DLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    Node<T>* cur;

    int numOfData;

public:
    void ListInit() {
        head = new Node<T>;
        tail = new Node<T>;

        head->prev = NULL;
        head->next = tail;

        tail->prev = head;
        tail->next = NULL;

        numOfData = 0;
    }

    void Linsert(T data) {
        Node<T>* newNode = new Node<T>;
        newNode->data = data;

        newNode->next = tail;
        newNode->prev = tail->prev;

        tail->prev->next = newNode;
        tail->prev = newNode;

        numOfData++;
    }

    bool LFirst(T& data) {
        if (head->next == tail) {
            return false;
        }

        cur = head->next;
        data = cur->data;

        return true;
    }
    bool LNext(T& data) {
        if (cur->next == tail) {
            return false;
        }

        cur = cur->next;

        data = cur->data;

        return true;
    }
    bool LPrevious(T& data) {
        if (cur->prev = head) {
            return false;
        }

        cur = cur->prev;

        data = cur->data;

        return true;
    }

    T LRemove() {
        Node<T>* rNode = cur;
        T rdata = rNode->data;

        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;

        cur = cur->prev;

        delete rNode;
        numOfData--;
        return rdata;
    }

    int LCount() {
        return numOfData;
    }

};

#endif