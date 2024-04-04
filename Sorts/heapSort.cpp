#include <iostream>
#include <ctime>
#include <vector>
#include <Windows.h>
using namespace std;

class Heap {
private:
	vector<int> heap = {};
	int size = 0;

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
	Heap(vector<int> _heap) {
		heap = _heap;
		size = _heap.size();
		int mid = (size / 2 - 1);
		for (int i = mid; i >= 0; i--) heapify(i);
	}

	vector<int> heapSort() {
		int len = size;
		for (int i = 0; i < len; i++) {
			swap(heap[0], heap[size - 1]);
			size--;
			heapify(0);
		}
		return heap;
	}

	void print() {
		for (int i = 0; i < heap.size(); i++) {
			cout << heap[i] << " ";
		}
		cout << endl;
	}

};


int main() {
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vector<int> arr = {};
	int n;
	cout << "Размер кучи: ";
	cin >> n;
	cout << "Массив рандомных чисел: ";
	for (int i = 0; i < n; i++) {
		int randEl = rand() % 100;
		cout << randEl << " ";
		arr.push_back(randEl);
	}
	cout << endl;
	cout << "Максимальная куча: ";
	Heap heap(arr);
	heap.print();
	cout << "Отсортируем: ";
	vector<int> sortedArr = heap.heapSort();
	for (int i : sortedArr) cout << i << " ";
	
	return 0;
}
