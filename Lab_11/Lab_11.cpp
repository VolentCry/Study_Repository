#include<iostream>
#include<string>
#include<clocale>
using namespace std;

struct Node {
	string data;
	Node* pointer_to_prev_node = nullptr;
	Node* pointer_to_next_node = nullptr;
};


struct List {
	Node* head_node = nullptr;
	Node* tail_node = nullptr;
};



void PrintList(List list) {
	Node* cur = list.head_node;
	while (cur != nullptr) {
		cout << cur->data << ' ';
		cur = cur->pointer_to_next_node;
	}
	delete cur;
	cout << endl;
}

void DestroyList(List& list) {
	Node* current = list.head_node;
	while (current != nullptr) {
		Node* next = current->pointer_to_next_node;
		delete current;
		current = next;
	}

	list.head_node = nullptr;
	list.tail_node = nullptr;
}

int ListLen(List list) {
	Node* cur = list.head_node;
	int lenght = 0;
	while (cur != nullptr) {
		lenght++;
		cur = cur->pointer_to_next_node;
	}
	delete cur;
	return lenght;
}

void InsertItem(List& list, const string& data, const int& index = 0) {
	Node* new_node = new Node;
	new_node->data = data;

	// Если список 
	if (list.head_node == nullptr) {
		list.head_node = new_node;
		list.tail_node = new_node;
		return;
	}

	// Вставка в начало
	if (index == 0) {
		new_node->pointer_to_next_node = list.head_node;
		list.head_node->pointer_to_prev_node = new_node;
		list.head_node = new_node;
		return;
	}

	int counter = 0;
	Node* current_node = list.head_node;

	while (current_node != nullptr && counter < index - 1) {
		current_node = current_node->pointer_to_next_node;
		++counter;
	}

	if (current_node == nullptr) {
		cout << "Ошибка: индекс вне диапазона" << endl;
		delete new_node;
		return;
	}

	new_node->pointer_to_prev_node = current_node;
	new_node->pointer_to_next_node = current_node->pointer_to_next_node;

	if (current_node->pointer_to_next_node != nullptr) {
		current_node->pointer_to_next_node->pointer_to_prev_node = new_node;
	}
	else {
		list.tail_node = new_node;
	}

	current_node->pointer_to_next_node = new_node;
}

void DeleteElementByKey(List& list, const string& del_str) {
	Node* current = list.head_node;
	while (current != nullptr) {
		if (current->data == del_str) {
			Node* toDelete = current; // Сохраняем удаляемый узел
			current = current->pointer_to_next_node; // Переходим к следующему до удаления

			if (toDelete == list.head_node && toDelete == list.tail_node) {
				// Единственный элемент
				list.head_node = nullptr;
				list.tail_node = nullptr;
			}
			else if (toDelete == list.head_node) {
				// Удаление "головы" списка
				list.head_node = toDelete->pointer_to_next_node;
				list.head_node->pointer_to_prev_node = nullptr;
			}
			else if (toDelete == list.tail_node) {
				// Удаление "хвоста" списка
				list.tail_node = toDelete->pointer_to_prev_node;
				list.tail_node->pointer_to_next_node = nullptr;
			}
			else {
				// Удаление из середины списка
				toDelete->pointer_to_prev_node->pointer_to_next_node = toDelete->pointer_to_next_node;
				toDelete->pointer_to_next_node->pointer_to_prev_node = toDelete->pointer_to_prev_node;
			}

			delete toDelete; // Удаление сохранённого узла
		}
		else {
			current = current->pointer_to_next_node;
		}
	}

}


int main() {
	List test_list;
	int K;
	setlocale(LC_ALL, "ru_RU.UTF-8");
	cout << endl;

	// Заполнение списка элементами для демонстрации
	InsertItem(test_list, "Apple", 0);
	InsertItem(test_list, "Orange", 1);
	InsertItem(test_list, "Banana", 2);

	// Печать списка
	PrintList(test_list);

	// Удаление элемента по ключу
	DeleteElementByKey(test_list, "Orange");

	// Печать списка
	PrintList(test_list);


	// Добавление K элементов в конец списка
	cout << "Введите количество элементов K: ";
	cin >> K;

	cout << "Вводите элементы:" << endl;
	for (int i = 0; i < K; ++i) {
		string input_data;
		cout << "Элемент " << (i + 1) << ": ";
		cin >> input_data;

		// Добавляем элемент в конец списка
		InsertItem(test_list, input_data, ListLen(test_list));
	}

	// Печать списка
	PrintList(test_list);

	return 0;
}