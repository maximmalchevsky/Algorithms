#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

class RBTree {
private:
    struct Node {
        int value;
        string color;
        Node* left, * right, * parent;
    };

    Node* root;
    Node* fictNode;

    Node* setNode(int value) {
        Node* node = new Node;
        node->parent = nullptr;
        node->value = value;
        node->left = fictNode;
        node->right = fictNode;
        node->color = "red";
        return node;
    }

    void leftRotation(Node* root) {
        Node* rRoot = root->right;
        root->right = rRoot->left;
        if (rRoot->left != fictNode) {
            rRoot->left->parent = root;
        }
        rRoot->parent = root->parent;
        if (root->parent == nullptr) {
            this->root = rRoot;
        }
        else if (root == root->parent->left) {
            root->parent->left = rRoot;
        }
        else {
            root->parent->right = rRoot;
        }
        rRoot->left = root;
        root->parent = rRoot;
    }

    Node* getMin(Node* root) {
        while (root->left != fictNode) {
            root = root->left;
        }
        return root;
    }

    Node* getMax(Node* root) {
        while (root->right != fictNode) {
            root = root->right;
        }
        return root;
    }

    void rightRotation(Node* root) {
        Node* lRoot = root->left;
        root->left = lRoot->right;
        if (lRoot->right != fictNode) {
            lRoot->right->parent = root;
        }
        lRoot->parent = root->parent;
        if (root->parent == nullptr) {
            this->root = lRoot;
        }
        else if (root == root->parent->right) {
            root->parent->right = lRoot;
        }
        else {
            root->parent->left = lRoot;
        }
        lRoot->right = root;
        root->parent = lRoot;
    }

    Node* findNode(Node* root, int value) {
        if (root == fictNode || root->value == value);
        if (value < root->value) {
            return findNode(root->left, value);
        }
        return findNode(root->right, value);
    }

    void fixDeletion(Node* node) {
        Node* leaf;
        while (node != root && node->color == "black") {
            if (node == node->parent->left) {
                leaf = node->parent->right;
                if (leaf->color == "red") {
                    leaf->color = "black";
                    node->parent->color = 'r';
                    leftRotation(node->parent);
                    leaf = node->parent->right;
                }

                if (leaf->left->color == "black" && leaf->right->color == "black") {
                    leaf->color = "red";
                    node = node->parent;
                }
                else {
                    if (leaf->right->color == "black") { 
                        leaf->left->color = "black";
                        leaf->color = "red";
                        rightRotation(leaf);
                        leaf = node->parent->right;
                    }

                    leaf->color = node->parent->color;
                    node->parent->color = "black";
                    leaf->right->color = "black";
                    leftRotation(node->parent);
                    node = root;
                }
            }
            else {
                leaf = node->parent->left;
                if (leaf->color == "red") {
                    leaf->color = "black";
                    node->parent->color = "red";
                    rightRotation(node->parent);
                    leaf = node->parent->left;
                }

                if (leaf->left->color == "black" && leaf->right->color == "black") {
                    leaf->color = "red";
                    node = node->parent;
                }
                else {
                    if (leaf->left->color == "black") {
                        leaf->right->color = "black";
                        leaf->color = "red";
                        leftRotation(leaf);
                        leaf = node->parent->left;
                    }

                    leaf->color = node->parent->color;
                    node->parent->color = "black";
                    leaf->left->color = "black";
                    rightRotation(node->parent);
                    node = root;
                }
            }
        }
        node->color = "black";
    }

    void swap(Node* one, Node* two) {
        if (one->parent == nullptr) {
            root = two;
        }
        else if (one == one->parent->left) {
            one->parent->left = two;
        }
        else {
            one->parent->right = two;
        }
        two->parent = one->parent;
    }

    void deleteNode(Node* root, int value) {
        Node* a;
        Node* b;
        Node* c = fictNode;
        while (root != fictNode) {
            if (root->value == value) {
                c = root;
            }

            if (root->value <= value) {
                root = root->right;
            }
            else {
                root = root->left;
            }
        }


        b = c;
        string bColor = b->color;
        if (c->left == fictNode) {
            a = c->right;
            swap(c, c->right);
        }
        else if (c->right == fictNode) {
            a = c->left;
            swap(c, c->left);
        }
        else {
            b = getMin(c->right);
            bColor = b->color;
            a = b->right;
            if (b->parent == c) {
                a->parent = b;
            }
            else {
                swap(b, b->right);
                b->right = c->right;
                b->right->parent = b;
            }

            swap(c, b);
            b->left = c->left;
            b->left->parent = b;
            b->color = c->color;
        }
        delete c;
        if (bColor == "black"){
            fixDeletion(a);
        }
    }

    void fixInsertion(Node* node) {
        Node* leaf;
        while (node->parent->color == "red") {
            if (node->parent == node->parent->parent->right) {
                leaf = node->parent->parent->left;
                if (leaf->color == "red") {
                    leaf->color = "black";
                    node->parent->color = "black";
                    node->parent->parent->color = "red";
                    node = node->parent->parent;
                }
                else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rightRotation(node);
                    }
                    node->parent->color = "black";
                    node->parent->parent->color = "red";
                    leftRotation(node->parent->parent);
                }
            }
            else {
                leaf = node->parent->parent->right;

                if (leaf->color == "red") {
                    leaf->color = "black";
                    node->parent->color = "black";
                    node->parent->parent->color = "red";
                    node = node->parent->parent;
                }
                else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        leftRotation(node);
                    }
                    node->parent->color = "black";
                    node->parent->parent->color = "red";
                    rightRotation(node->parent->parent);
                }
            }
            if (node == root) {
                break;
            }
        }
        root->color = "black";
    }

    void printTree(Node* root) {
        if (root == nullptr) return;
        cout << root->value << " : " << root->color << endl;
        printTree(root->left);
        printTree(root->right);
    }

    void addNode(int value) {
        Node* node = setNode(value);

        Node* y = nullptr;
        Node* x = this->root;

        while (x != fictNode) {
            y = x;
            if (node->value < x->value) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        }
        else if (node->value < y->value) {
            y->left = node;
        }
        else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = 'b';
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        fixInsertion(node);
    }



public:
    RBTree() {
        fictNode = new Node;
        fictNode->color = "black";
        fictNode->value = NULL;
        fictNode->left = nullptr;
        fictNode->right = nullptr;
        root = fictNode;
    }

    void add(int value) {
        addNode(value);
    }

    void del(int value) {
        deleteNode(this->root, value);
    }

    void print() {
        if (root) {
            printTree(this->root);
        }
    }

};



int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));
    RBTree tree;
    cout << "Дерево: " << endl;
    tree.add(13);
    tree.add(8);
    tree.add(17);
    tree.add(1);
    tree.add(11);
    tree.add(6);
    tree.add(15);
    tree.add(25);
    tree.add(22);
    tree.add(27);
    tree.print();
    
    cout << endl << "Удалим 25: " << endl;
    tree.del(25);
    tree.print();

    return 0;
}
