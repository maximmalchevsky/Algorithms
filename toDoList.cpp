#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;

class Heap {
private:
	vector<string> toDo = {};
	vector<int> priority = {};
	vector<bool> completed = {};
	int size = 0;

	void fixHeap(int index) {
		if (index == 0) return;
		int parent = (index % 2 == 0) ? index / 2 : (index - 1) / 2;
		if (priority[parent] < priority[index]) {
			swap(toDo[parent], toDo[index]);
			swap(priority[parent], priority[index]);
			swap(completed[parent], completed[index]);
			fixHeap(parent);
		}
	}

	void heapify(int index) {
		int left = (index * 2 + 1 < size) ? priority[index * 2 + 1] : 0;
		int right = (index * 2 + 2 < size) ? priority[index * 2 + 2] : 0;
		if (priority[index] < left && left >= right) {
			swap(priority[index], priority[index * 2 + 1]);
			swap(toDo[index], toDo[index * 2 + 1]);
			swap(completed[index], completed[index * 2 + 1]);
			heapify(index * 2 + 1);
		}
		else if (priority[index] < right && right > left) {
			swap(priority[index], priority[index * 2 + 2]);
			swap(toDo[index], toDo[index * 2 + 2]);
			swap(completed[index], completed[index * 2 + 2]);
			heapify(index * 2 + 2);
		}
	}

public:

	void add(string task, int _priority) {
		toDo.push_back(task);
		priority.push_back(_priority);
		completed.push_back(false);
		size++;
		fixHeap(size - 1);
	}

	void mostImportant() {
		if (size == 0) cout << "Пока дел нет!" << endl;
		else {
			cout << "Самое важное дело: " << endl;
			cout << "Приоритет: " << priority[0] << " " << "Задание: " << toDo[0] << " " << "Выполнение: " << completed[0] << endl;
		}
	} 

	void print() {
		cout << "Список ваших дел:" << endl;
		for (int i = 0; i < size; i++) cout << i << ")" << "Приоритет: " << priority[i] << " " << "Задание: " << toDo[i] << " " << "Выполнение: " << completed[i] << endl;
		cout << endl;
	}

	void complete() {
		if (completed[0]) cout << "Все задания сделаны." << endl;
		else {
			completed[0] = true;
			priority[0] = 0;
			heapify(0);
		}
	}

	void pop() {
		cout << "Было удалено задание: " << endl;
		cout << "Приоритет: " << priority[0] << " " << "Задание: " << toDo[0] << " " << "Выполнение: " << completed[0] << endl;
		swap(toDo[0], toDo[size - 1]);
		swap(priority[0], priority[size - 1]);
		swap(completed[0], completed[size - 1]);
		toDo.pop_back();
		priority.pop_back();
		completed.pop_back();
		size--;
		heapify(0);
	}

	void rename(int index, string name) {
		toDo[index] = name;
	}
};

void menu() {
	Heap toDoList;
	cout << "Список команд: " << endl;
	cout << "/important - получить задание с наивысшим приоритетом" << endl << "/complete - выполнить задание с наивысшим приоритетом" << endl;
	cout << "/delete - удалить задание с наивысшим приоритетом" << endl;
	cout << "/add [текст задания] [приоритет] - добавить задание" << endl;
	cout << "/rename [id] [новый текст] - переименовать задание" << endl;
	cout << "/print - вывести список дел" << endl << "/exit - выйти" << endl << endl;

	string command;
	while (true) {
		cin >> command;
		if (command == "/important") toDoList.mostImportant();
		else if (command == "/complete") toDoList.complete();
		else if (command == "/add") {
			int priority;
			string task;
			cin >> task >> priority;
			toDoList.add(task, priority);
		}
		else if (command == "/print") toDoList.print();
		else if (command == "/delete") toDoList.pop();
		else if (command == "/rename") {
			int index;
			string name;
			cin >> index >> name;
			toDoList.rename(index, name);
		}
		else if (command == "/exit") break;

	}
}


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	menu();
	return 0;
}
