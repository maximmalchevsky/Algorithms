#include <iostream>
using namespace std;

class MyStack {
private:
  class Node {
  public:
    int value;
    Node* next;
    
    Node(int _value) :value(_value), next(nullptr) {};
  };
  Node* top;
  int len;
public:
  MyStack() :top(nullptr), len(0) {};

  void push(int key) {
    Node* newNode = new Node(key);
    newNode->next = top;
    top = newNode;
    len++;
  }

  void pop() {
    if (top != nullptr) {
      cout << top->value << endl;
      Node* temp = top;
      top = top->next;
      len--;
    }
  }

  void back() {
    cout << top->value << endl;
  }

  void size() {
    cout << len << endl;
  }

  void clear() {
    while (top != nullptr) {
      Node* temp = top;
      top = top->next;
      delete temp;
    }
    len = 0;
  }
};
