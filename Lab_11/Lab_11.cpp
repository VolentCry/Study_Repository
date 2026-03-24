#include<iostream>
using namespace std;

struct Node {
	int data;
	Node* pointer_to_prev_node = nullptr;
	Node* pointer_to_next_node = nullptr;
};


struct List {
	Node* head_node = nullptr;
	Node* tail_node = nullptr;
};


void InsertItem(List& list, const int& data, const int& index = 0) {
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
	
int main() {
	List list;
	
	return 0;
}