#pragma once
#include "petshop/include/ds/LinkedList.hpp"
#include <iostream>

LinkedList::LinkedList() {
    head = nullptr;
    size = 0;
}
LinkedList::LinkedList(Node<T> &value) {
    head = &value;
    size = 1;
}
LinkedList::~LinkedList() {
    while (head != nullptr) {
        Node<T> *temp = head;
        head = head->next;
        delete *temp;
    }
}
Node<T> LinkedList::getLinkedList() {
    while (head != nullptr) {
        cout << head->getNode() << " ";
        head = head->next;
    }
}