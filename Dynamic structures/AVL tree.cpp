#include <iostream>
#include <ctime>
#include <Windows.h>
using namespace std;

class Avl {
private:
	struct Node {
		int value;
		Node* left, * right;
		Node(int _value) : value(_value), left(nullptr), right(nullptr) {};
	};

	Node* root;

	int getDepth(Node* root) {
		if (root == nullptr) return 0;
		int depthLeft = getDepth(root->left);
		int depthRight = getDepth(root->right);
		return max(depthLeft, depthRight) + 1;
	}

	int getBalance(Node* root) {
		return (root == nullptr) ? 0 : getDepth(root->right) - getDepth(root->left);
	}

	void printTree(Node* root) {
		if (root == nullptr) return;
		cout << root->value << ":" << getBalance(root) << endl;
		printTree(root->left);
		printTree(root->right);
	}

	Node* getMin(Node* root) {
		return root->left ? getMin(root->left) : root;
	}

	Node* removeMin(Node* root) {
		if (!root->left) {
			return root->right;
		}
		root->left = removeMin(root->left);
		return balance(root);
	}

	Node* remove(Node* root, int value) {
		if (!root) return nullptr;
		if (value < root->value) root->left = remove(root->left, value);
		else if (value > root->value) root->right = remove(root->right, value);
		else {
			Node* l = root->left;
			Node* r = root->right;
			delete root;
			if (!r) return l;
			Node* min = getMin(r);
			min->right = removeMin(r);
			min->left = l;
			return balance(min);
		}
		return balance(root);

	}

	Node* addNode(Node* root, int value) {
		if (root == nullptr) {
			return new Node(value);
		}
		if (value > root->value) root->right = addNode(root->right, value);
		else if (value < root->value) root->left = addNode(root->left, value);
		return balance(root);
	}

	Node* rotateRight(Node* root) {
		Node* leftRoot = root->left;
		root->left = leftRoot->right;
		leftRoot->right = root;
		return leftRoot;
	}

	Node* rotateLeft(Node* root) {
		Node* rightRoot = root->right;
		root->right = rightRoot->left;
		rightRoot->left = root;
		return rightRoot;
	}

	
	Node* balance(Node* pivot) {
		if (getBalance(pivot) == 2) {
			if (getBalance(pivot->right) < 0) {
				pivot->right = rotateRight(pivot->right);
			}
			return rotateLeft(pivot);
		}

		if (getBalance(pivot) == -2) {
			if (getBalance(pivot->left) > 0) {
				pivot->left = rotateLeft(pivot->left);
			}
			return rotateRight(pivot);
		}
		return pivot;
	}



public:
	Avl() :root(nullptr) {};

	void add(int value) {
		root = addNode(root, value);
	}

	void print() {
		printTree(root);
		cout << endl;
	}

	void remove(int value){
		root = remove(root, value);
};
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));

	Avl tree;

	cout << "Создадим дерево из 10 рандомных элементов от 0 до 100 и выведем баланс каждого узла: " << endl;
	for (int i = 0; i <= 9; i++) {
		tree.add(rand()% 100);
	}
	tree.print();

	cout << "Добавим 3 элемента - 20, 41 и 1000: " << endl;
	tree.add(20);
	tree.add(41);
	tree.add(1000);
	tree.print();

	cout << "Удалим 41: " << endl;
	tree.remove(41);
	tree.print();

	return 0;
}
