#include <iostream>
#include <ctime>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
};

Node* createNode(int value) {
    Node* root = new Node();
    root->value = value;
    root->left = root->right = nullptr;
    return root;
}

void Insert(Node*& root, int value) {
    if (root == nullptr) root = createNode(value);
    else if (root->value > value) Insert(root->left, value);
    else Insert(root->right, value);
}

void printTree(Node* root) {
    if (root != nullptr) {
        cout << root->value << " ";
        printTree(root->left);
        printTree(root->right);
    }
}

int depthTree(Node* root) {
    if (root == nullptr) return 0;
    int depthLeft = depthTree(root->left);
    int depthRight = depthTree(root->right);

    return max(depthLeft, depthRight) + 1;
}

Node* searchNode(Node* root, int value) {
    while (root != nullptr && root->value != value) {
        root = (value < root->value) ? root->left : root->right;
    }
    return root;
}

Node* searchParent(Node* root, int value) {
    if (root == nullptr || root->value == value) return nullptr;
    else {
        if (root->left && root->left->value == value) return root;
        else if (root->value == value) return nullptr;
        else if (root->right != nullptr && root->right->value == value) return root;
        else if (root->value > value) return searchParent(root->left, value);
        else if (root->value < value) return searchParent(root->right, value);
    }
}

Node* searchMax(Node* root) {
    if (root == nullptr) return nullptr;
    if (root->right == nullptr) return root;
    else return searchMax(root->right);
}

void deleteNode(Node* root, int value) {
    Node* node = searchNode(root, value);
    Node* parent = searchParent(root, value);

   
    if (node->left == nullptr && node->right == nullptr) {
        if (parent->value > value) parent->left = nullptr;
        else parent->right = nullptr;
        delete node;
    }

    else if (node->left == nullptr && node->right != nullptr) {
        if (parent->value > value) parent->left = node->right;
        else parent->right = node->right;
    }
    
    else if (node->left != nullptr && node->right == nullptr) {
        if (parent->value > value) parent->left = node->left;
        else parent->right = node->left;
    }

    else if (node->left->right == nullptr) {
        if (parent->value > value) {
            parent->left = node->left;
            node->left->right = node->right;
        }
        else{
            parent->right = node->left;
            node->left->right = node->right;
        }
    }
    
    else if (node->left != nullptr && node->right != nullptr) {
        Node* max = searchMax(node->left);
        searchParent(root, max->value)->right = nullptr;
        if (parent->value > value) {
            parent->left = max;
            max->right = node->right;
        }
        else {
            parent->right = max;
            max->right = node->right;
        }
    }
}

int main() {
    srand(time(0));
    setlocale(LC_ALL, "russian");
    cout << "Введите число элементов дерева: ";
    int n; cin >> n;
    Node* root = nullptr;
    for (int i = 0; i < n; i++) {
        Insert(root, rand() % 100);
    }
    cout << "Напечатаем получившееся дерево: "; printTree(root);
    cout << endl << "Добавим в дерево элемент 11";
    Insert(root, 11);
    cout << endl << "Напечатаем дерево с введенным элементом: "; printTree(root);
    
    cout << endl << "Найдем глубину дерева: " << depthTree(root) << endl;
    cout << "Адрес ячейки с числом 11: " << searchNode(root, 11) << endl;
    deleteNode(root, 11);
    
    cout << "Удалим число 11 из дерева: "; printTree(root);
}
