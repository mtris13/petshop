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
*/

template <typename T>

class Node {
private:
    T data;
    Node *next;

public:
    // Ham dung
    Node();
    Node(T &value);

    // Ham huy
    ~Node();
    // Getter
    T getNode();

    // Setter
    void setNode(const T &);
};
// Ham dung
template <typename T>
Node<T>::Node() : next(nullptr) {
    data = new T;
}

template <typename T>
Node<T>::Node(T &value) : next(nullptr) {
    data = new T;
    data = value;
}

// Ham huy
template <typename T>
Node<T>::Node() {
}

// Getter
template <typename T>
T Node<T>::getNode() {
    return data;
}

// Setter
template <typename T>
void Node<T>::setNode(const T &value) {
    data = value;
}