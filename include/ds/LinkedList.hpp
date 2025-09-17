#pragma once
#include "Node.hpp"
#include <iostream>

/*
LƯU Ý: trước mỗi hàm phải có dòng "template <typename T>"

Thứ tự các hàm:
    Constructor
    Destuctor
    Getter: ham const
    Setter
    Overloading operator
    Display
    Others
*/

template <typename T>

class LinkedList {
private:
    Node<T> *head;
    int size;

public:
    // Ham dung
    LinkedList();
    LinkedList(const T &value);

    // Ham huy
    ~LinkedList();

    // Getter
    Node<T> *getHead() const;
    int getSize() const;
    // Setter
    // void setLinkedList(const LinkedList<T> &);

    // Operator

    // Display
    void printLinkedList();

    // Others
    bool isEmpty() const;
    void pushBack(const T &value);
    void pushFront(const T &value);
};

// Ham dung
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), size(0) {}

template <typename T>
LinkedList<T>::LinkedList(const T &value) : size(1), head(new Node<T>(value)) {}

// Ham huy
template <typename T>
LinkedList<T>::~LinkedList() {
    while (head != nullptr) {
        Node<T> *temp = head;
        head = head->getNext();
        delete temp;
    }
}

// Getter
template <typename T>
Node<T> *LinkedList<T>::getHead() const {
    return head;
}

template <typename T>
int LinkedList<T>::getSize() const {
    return size;
}

// Setter
// template <typename T>
// void LinkedList<T>::setLinkedList(const LinkedList<T> &value) {

// }

// Display
template <typename T>
void LinkedList<T>::printLinkedList() {
    Node<T> *temp = head;
    while (temp != nullptr) {
        temp->printData();
        std::cout << " ";
        temp = temp->getNext();
    }
    cout << endl;
}

// Others
template <typename T>
bool LinkedList<T>::isEmpty() const {
    return head == nullptr;
}

template <typename T>
void LinkedList<T>::pushBack(const T &value) {
    Node<T> *newNode = new Node<T>(value);
    if (!head) {
        head = newNode;
    } else {
        Node<T> *temp = head;
        while (temp->getNext() != nullptr) {
            temp = temp->getNext();
        }
        temp->setNext(newNode);
    }
    size++;
}

template <typename T>
void LinkedList<T>::pushFront(const T &value) {
    Node<T> *newNode = new Node<T>(value);
    newNode->setNext(head);
    head = newNode;
    size++;
}