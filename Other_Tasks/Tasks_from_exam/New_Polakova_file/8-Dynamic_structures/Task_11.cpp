/*
Напиши программу, реализующую очередь. Узел Node оставляем точно таким же, как в стеке.

1. Добавление (Enqueue): Напиши функцию void enqueue(Node*& head, Node*& tail, int value).
	- Создай новый узел.
	- Если очередь пустая (head == nullptr), то и head, и tail должны указывать на этот новый узел (он первый и единственный).
	- Если очередь не пустая, привяжи новый узел к текущему хвосту (tail->next_ptr = new_node;), а затем сделай новый узел актуальным хвостом (tail = new_node;).
2. Удаление (Dequeue): Напиши функцию void dequeue(Node*& head, Node*& tail).
	- Она работает почти так же, как правильный pop в стеке: берем head, запоминаем во временный указатель, сдвигаем head на следующий элемент и делаем delete temp;.
	- Нюанс: Если после удаления элемента очередь стала пустой (head == nullptr), не забудь обнулить и tail (tail = nullptr;), чтобы он не указывал на удаленный мусор.
3. Вывод на экран: Можешь использовать ту же функцию printQueue, что и для стека (она просто идет от head до конца).
4. В main: * Создай Node* head = nullptr; и Node* tail = nullptr;.
	- Добавь числа 1, 2, 3 (enqueue). Выведи очередь (должно быть 1 2 3).
	- Удали один элемент (dequeue). Должна удалиться единица, так как она пришла первой! Выведи очередь (должно остаться 2 3).
*/

#include <iostream>
#include <clocale>
using namespace std;

struct Node {
	int data;
	Node* next_ptr;
};

void enqueue(Node*& head, Node*& tail, int value) {
	Node* new_node = new Node; // Создаём новый узел
	new_node->data = value;
	new_node->next_ptr = nullptr;
	if (head == nullptr) {
		head = new_node;
		tail = new_node;
	}
	else {
		tail->next_ptr = new_node;
		tail = new_node;
	}

	return;
}


void dequeue(Node*& head, Node*& tail) {
	if (head == nullptr) {
		cout << "Очередь пуста. Удалять нечего." << endl;
	}
	else if (head == tail) {
		head = nullptr;
		tail = nullptr;
	}
	else {
		Node* current = head->next_ptr; // СОхраняем указатель на втолрой элемент с начала
		head = current;
	}
	return;
}

void printQueue(Node*& head) {
	if (head == nullptr) {
		cout << "Очередь пуста!";
		return;
	}

	Node* current = head;
	while (current != nullptr) {
		cout << current->data << " ";
		current = current->next_ptr;
	}
	cout << endl;

	return;
}

int main() {
	setlocale(LC_ALL, "Russian");

	// Создаём пустую очередь
	Node* head = nullptr;
	Node* tail = nullptr;

	enqueue(head, tail, 15);
	enqueue(head, tail, 25);
	enqueue(head, tail, 55);
	enqueue(head, tail, 75);

	printQueue(head);

	dequeue(head, tail);

	printQueue(head);
}