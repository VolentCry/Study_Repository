#include<iostream>
#include<string>
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

void DeleteElement(List& list, const string& del_str) {
	Node* current = list.head_node;
	while (current != nullptr) {
		if (current->data == del_str) {
			Node* toDelete = current; // Сохраняем удаляемый узел
			current = current->pointer_to_next_node; // Переходим к следующему до удаления

			if (toDelete == list.head_node && toDelete == list.tail_node) {
				// Единственный элемент
				list.head_node = nullptr;
				list.tail_node = nullptr;
			} else if (toDelete == list.head_node) {
				// Удаление "головы" списка
				list.head_node = toDelete->pointer_to_next_node;
				list.head_node->pointer_to_prev_node = nullptr;
			} else if (toDelete == list.tail_node) {
				// Удаление "хвоста" списка
				list.tail_node = toDelete->pointer_to_prev_node;
				list.tail_node->pointer_to_next_node = nullptr;
			} else {
				// Удаление из середины списка
				toDelete->pointer_to_prev_node->pointer_to_next_node = toDelete->pointer_to_next_node;
				toDelete->pointer_to_next_node->pointer_to_prev_node = toDelete->pointer_to_prev_node;
			}

			delete toDelete; // Удаление сохранённого узла
		} else {
			current = current->pointer_to_next_node;
		}
	}

}
	
int main() {
	List test_list;
	int N = 5;
	cout << "\n";
	InsertItem(test_list, "FFF", 0);
	InsertItem(test_list, "DDD", 1);
	InsertItem(test_list, "SSS", 2);
	PrintList(test_list);
	DeleteElement(test_list, "DDD");
	PrintList(test_list);
	return 0;
}