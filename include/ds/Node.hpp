#pragma once
#include <iostream>
/*
LƯU Ý: trước mỗi hàm phải có dòng "template <typename T>"

Thứ tự các hàm:
    Constructor
    Destuctor
    Getter
    Setter
    Overloading operator
    Display
    Others

    trả về con trỏ thì không nên dùng kiểu const
*/

template <typename T>

class Node {
private:
    T data;
    Node *next;

public:
    // Ham dung
    Node();
    Node(const T &value);

    // Ham huy
    ~Node();
    // Getter
    T getData() const;
    Node *getNext() const;

    // Setter
    void setData(const T &);
    void setNext(Node<T> *nextValue);

    // Display
    void printData();
};

// Ham dung
template <typename T>
Node<T>::Node() : next(nullptr) {
    data = T(); // gán giá trị mặc định của T cho data
}

template <typename T>
Node<T>::Node(const T &value) : next(nullptr) {
    data = value;
}

// Ham huy
template <typename T>
Node<T>::~Node() {
}

// Getter
template <typename T>
T Node<T>::getData() const {
    return data;
}

template <typename T>
Node<T> *Node<T>::getNext() const {
    return next;
}

// Setter
template <typename T>
void Node<T>::setData(const T &value) {
    data = value;
}

template <typename T>
void Node<T>::setNext(Node<T> *nextValue) {
    next = nextValue;
}

// Display

template <typename T>
void Node<T>::printData() {
    cout << data;
}