#include "ds/LinkedList.hpp"
#include <iostream>
using namespace std;

void testLinkedList() {
  LinkedList<int> list;

  cout << "=== Test pushBack ===\n";
  list.pushBack(10);
  list.pushBack(20);
  list.pushBack(30);
  list.printLinkedList(); // 10 20 30

  cout << "=== Test pushFront ===\n";
  list.pushFront(5);
  list.pushFront(1);
  list.printLinkedList(); // 1 5 10 20 30

  cout << "=== Test popFront ===\n";
  list.popFront();
  list.printLinkedList(); // 5 10 20 30

  cout << "=== Test popBack ===\n";
  list.popBack();
  list.printLinkedList(); // 5 10 20

  cout << "=== Test insert ===\n";
  list.insert(1, 7);      // chèn 7 vào vị trí 1
  list.printLinkedList(); // 5 7 10 20

  cout << "=== Test erase ===\n";
  list.erase(2);          // xóa phần tử tại vị trí 2
  list.printLinkedList(); // 5 7 20

  cout << "=== Test swap ===\n";
  int a = 100, b = 200;
  cout << "Before swap: a=" << a << " b=" << b << endl;
  list.swap(a, b);
  cout << "After swap: a=" << a << " b=" << b << endl;

  cout << "=== Final LinkedList ===\n";
  list.printLinkedList();
}

int main() {
  testLinkedList();
  return 0;
}
