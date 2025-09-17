#pragma once
#include "Node.hpp"
#include <iostream>
using namespace std;

/*
LƯU Ý: trước mỗi hàm phải có dòng "template <typename T>"

Thứ tự các hàm:
    Constructor
    Destuctor
    Getter
    Setter
    Overloading operator
    Display
*/

template <typename T>

class LinkedList {
private:
    Node<T> *head;
    int size;

public:
    // Ham dung
    LinkedList();
    LinkedList(Node<T> &value);

    // Ham huy
    ~LinkedList();

    // Getter
    Node<T> getLinkedList();

    // Setter

    // Operator

    // Display
};

// Ham dung
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), size(0) {}

template <typename T>
LinkedList<T>::LinkedList(Node<T> &value) {
    head = &value;
    size = 1;
}

// Ham huy
template <typename T>
LinkedList<T>::~LinkedList() {
    while (head != nullptr) {
        Node<T> *temp = head;
        head = head->next;
        delete *temp;
    }
}

// Getter
template <typename T>
Node<T> LinkedList<T>::getLinkedList() {
    while (head != nullptr) {
        cout << head->getNode() << " ";
        head = head->next;
    }
}
