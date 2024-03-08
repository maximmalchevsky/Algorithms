#include <iostream>
using namespace std;



//В списке будем хранить наименование товара(string), кол - во упаковок(int), массу одной упаковки(double)

struct Node {
    string name;
    int value;
    double mass;
    Node* next;

};


Node* newNode(string name, int value, double mass) {
    Node* node = new Node();

    node->next = nullptr;
    node->name = name;
    node->value = value;
    node->mass = mass;

    return node;
}

//печать списка
void printList(Node* &head) {
    Node* ptr = head;
    while (ptr != nullptr) {
        cout << "Название товара: " << ptr->name << ", "  <<"Кол-во упаковок: " << ptr->value << " шт,  " << "Масса одной упаковки: " << ptr->mass <<" кг;" << endl;
        ptr = ptr->next;
    } 
    cout << endl;
}

//вставка в конец
void pushBack(Node*& head, string name, int value, double mass) {
    if (head == nullptr) head = newNode(name, value, mass);
    else {
        Node* ptr = head;
        while (ptr->next != nullptr) ptr = ptr->next;
        ptr->next = newNode(name, value, mass);
    }
}

//вставка в начало
void pushForward(Node*& head, string name, int value, double mass) {
    Node* node = newNode(name, value, mass);
    node->next = head;
    head = node;

}



void insertAfter(Node* head, string name, int value, double mass, string nameAfter)
{
    if (head == nullptr) return;
    Node* ptr = head;
    while (ptr != nullptr && ptr->name != nameAfter)
        ptr = ptr->next;
    if (ptr == nullptr) return;
    Node* newNode = new Node;
    newNode->name = name;
    newNode->value = value;
    newNode->mass = mass;
    newNode->next = ptr->next;
    ptr->next = newNode;
}


void insertBefore(Node*& head, string name, int value, double mass, string nameBefore)
{
    if (head == nullptr) return;
    if (head->name == nameBefore){
        pushForward(head, name, value, mass); 
        return;
    }
    if (head->next == nullptr) return;
    Node* prev = head, * ptr = head->next;
    while (ptr->next != nullptr && ptr->name != nameBefore)
    {
        prev = prev->next; ptr = ptr->next;
    }
    if (ptr->next == nullptr && ptr->name != nameBefore)
        return;
    Node* newNode = new Node;
    newNode->name = name;
    newNode->value = value;
    newNode->mass = mass;
    newNode->next = ptr;
    prev->next = newNode;
 
}



 void delNode(Node*& head, string name)
{
    if (head == nullptr) return;
    Node* ptr = head;
    if (head->name == name)
    {
        head = head->next; 
        delete ptr; 
        return;
    }
    if (head->next == nullptr) return;
    Node* prev = head; ptr = head->next;
    while (ptr->next != nullptr && ptr->name != name)
    {
        prev = prev->next; 
        ptr = ptr->next;
    }
    if (ptr->next == nullptr && ptr->name != name)
        return;
    prev->next = ptr->next;
    delete ptr;
}



int main() {
    setlocale(LC_ALL, "russian");
    Node* head = nullptr;

    cout << "Добавим первые 2 товара в конец списка: " << endl;
    pushBack(head, "Клубника", 2, 0.25);
    pushBack(head, "Помидоры", 11, 0.75);
    printList(head);
  
    cout << "Удалим из списка помидоры: " << endl;
    delNode(head, "Помидоры");
    printList(head);


    cout << "Добавим молоко в начало списка: " << endl;
    pushForward(head, "Молоко", 3, 0.935);
    printList(head);
    

    cout << "Добавим в список мороженое после клубники: " << endl;
    insertAfter(head, "Мороженое", 7, 0.125, "Клубника");
    printList(head);
    
    cout << "Добавим в список кашу до мороженного: " << endl;
    insertBefore(head, "Каша", 10, 0.037, "Мороженое");
    printList(head);

    
    return 0;

}
