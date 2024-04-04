#include <iostream>
#include <ctime>
#include <vector>
#include <Windows.h>
using namespace std;

class Heap {
private:
	vector<int> heap = {};
	int size = 0;

	void fixHeap(int index) {
		if (index == 0) return;
		int parent = (index % 2 == 0) ? (index / 2) : (index - 1) / 2;
		if (heap[parent] < heap[index]) {
			swap(heap[parent], heap[index]);
			fixHeap(parent);
		}
	}

	void heapify(int index) {
		int left = (index * 2 + 1 < size) ? heap[index * 2 + 1] : 0;
		int right = (index * 2 + 2 < size) ? heap[index * 2 + 2] : 0;
		if (heap[index] < left && left >= right) {
			swap(heap[index], heap[index * 2 + 1]);
			heapify(index * 2 + 1);
		}
		else if (heap[index] < right && right > left) {
			swap(heap[index], heap[index * 2 + 2]);
			heapify(index * 2 + 2);
		}
	}
public:
	Heap() {}
	Heap(vector<int> _heap) {
		heap = _heap;
		size = _heap.size();
		int mid = (size / 2 - 1);
		for (int i = mid; i >= 0; i--) heapify(i);
	}

	void add(int value) {
		heap.push_back(value);
		size++;
		fixHeap(size - 1);
	}

	void print() {
		for (int i = 0; i < heap.size(); i++) {
			cout << heap[i] << " ";
		}
		cout << endl;
	}

	int getMax() {
		return heap[0];
	}

	int pop() {
		int max = heap[0];
		swap(heap[0], heap[size - 1]);
		heap.pop_back();
		size--;
		heapify(0);
		return max;
	}

	void mergeHeap(Heap* secondHeap) {
		for (int i : secondHeap->heap) add(i);
	}
};


int main() {
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vector<int> arr = {};

	int n;
	cout << "Размер первой кучи: ";
	cin >> n;
	cout << "Массив рандомных чисел: ";
	for (int i = 0; i < n; i++) {
		int randEl = rand() % 100;
		cout << randEl << " ";
		arr.push_back(randEl);
	}
	cout << endl;
	cout << "Первая куча: ";
	Heap* heap1 = new Heap(arr);
	heap1->print();
	cout << "Максимум кучи: " << heap1->getMax() << endl;
	cout << "Удалим максимальный элемент из первой кучи: ";
	heap1->pop();
	heap1->print();
	cout << "Размер второй кучи: ";
	cin >> n;
	Heap* heap2 = new Heap();
	for (int i = 0; i < n; i++) heap2->add(rand() % 100);
	cout << "Вторая куча: ";
	heap2->print();
	cout << "Слияние двух куч: ";
	heap1->mergeHeap(heap2);
	heap1->print();
	return 0;
}
