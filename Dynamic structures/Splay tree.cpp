#include <iostream>
#include <Windows.h>
#include <ctime>
using namespace std;

class Splay {
private:
	struct Node {
		int value;
		Node* left, * right;
		Node(int _value) : value(_value), left(nullptr), right(nullptr) {};
	};
	
	Node* root;

	Node* rightRotation(Node* root) {
		Node* left = root->left;
		root->left = left->right;
		left->right = root;
		return left;
	}

	Node* leftRotation(Node* root) {
		Node* right = root->right;
		root->right = right->left;
		right->left = root;
		return right;
	}

	Node* splay(Node* root, int value) {
		if (root == nullptr || root->value == value) return root;

		if (root->value > value) {
			if (root->left == nullptr) return root;
			if (root->left->value > value) {
				root->left->left = splay(root->left->left, value);
				root = rightRotation(root);
			}
			else if (root->left->value < value) {
				root->left->right = splay(root->left->right, value);
				if (root->left->right != nullptr)
					root->left = leftRotation(root->left);
			}
			return (root->left == nullptr) ? root : rightRotation(root);
		}
		else {

			if (root->right == nullptr) return root;

			if (root->right->value > value) {
				root->right->left = splay(root->right->left, value);
				if (root->right->left != nullptr)
					root->right = rightRotation(root->right);
			}
			else if (root->right->value < value) {
				root->right->right = splay(root->right->right, value);
				root = leftRotation(root);
			}

			return (root->right == nullptr) ? root : leftRotation(root);
		}
	}

	Node* addNode(Node* root, int value) {
		if (root == nullptr) return new Node(value);
		if (root->value > value) root->left = addNode(root->left, value);
		else root->right = addNode(root->right, value);
		return root;
	}

	Node* deleteNode(Node* root, int value) {
		if (root == nullptr) return root;
		root = splay(root, value);
		if (value != root->value) return root;

		Node* tmp;
		if (root->left == nullptr) {
			tmp = root;
			root = root->right;
		}
		else {
			tmp = root;
			root = splay(root->left, value);
			root->right = tmp->right;
		}
		delete tmp;
		return root;
	}

	void printTree(Node* root) {
		if (root == nullptr) return;
		cout << root->value << endl;
		printTree(root->left);
		printTree(root->right);
	}

public:
	Splay() : root(nullptr) {};

	void add(int value) {
		root = addNode(root, value);
		root = splay(root, value);
	}

	void del(int value) {
		root = deleteNode(root, value);
	}

	void print() {
		printTree(root);
	}
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));
	Splay tree;
	cout << "Заполним дерево 10 рандомными элементами от 1 до 100: " << endl;
	for (int i = 0; i < 10; i++) tree.add(rand() % 100);
	tree.print();

	cout << "Добавим в дерево 3 элемента(11, 43): " << endl;
	tree.add(11);
	tree.add(43);
	tree.print();

	cout << "Удалим 43: " << endl;
	tree.del(43);
	tree.print();
	return 0;
}
