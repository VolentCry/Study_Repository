/*
1. Описание структуры: Создай структуру Node (узел), в которой будет храниться целое число (data) и указатель на следующий узел (Node* next).
2. Добавление (Push): Напиши функцию void push(Node*& head, int value). Она должна динамически создавать новый узел, класть туда value, указывать его next на текущую head, а затем делать этот новый узел новой «головой». (Обрати внимание на передачу указателя по ссылке Node*& — это нужно, чтобы изменения адреса головы сохранились в main).
3. Удаление (Pop): Напиши функцию void pop(Node*& head). Она должна выводить на экран значение верхнего элемента (головы), затем запоминать адрес старой головы во временный указатель, смещать саму head на следующий элемент (head->next), а старую голову — удалять из памяти (delete), чтобы не было утечек. Если стек пуст, функция должна просто сообщать об этом.
4. Вывод на экран: Напиши функцию void printStack(Node* head), которая с помощью цикла while пройдет от головы до конца (nullptr) и выведет все элементы.
5. Уничтожение (обязательный пункт из твоего билета): Напиши функцию void clearStack(Node*& head), которая в цикле удаляет все элементы до тех пор, пока стек не станет полностью пустым.
6. Демонстрация в main: - Создай пустой стек (объяви указатель Node* head = nullptr;).

 - Добавь в него числа 10, 20 и 30 (именно в таком порядке).
 - Выведи стек на экран (должно вывестись 30, 20, 10, так как 30 добавили последним, и она лежит на самом верху)
 - Вызови pop один раз (должно удалиться число 30).
 - Снова выведи стек.
 - Вызови функцию уничтожения стека.
*/

#include <iostream>
#include <clocale>
using namespace std;

struct Node {
	int data;
	Node* next_ptr;
};

void printStack(Node*& head) {
	if (head == nullptr) {
		cout << "Стек пуст";
		return;
	}

	Node* current = head;

	while (current != nullptr) {
		cout << current->data << " ";
		current = current->next_ptr; // Шагаем на следующий элемент
	}
	cout << endl;
}

void push(Node*& top, int new_data) {
	Node* new_node = new Node;  // Создаём новый узел в динамической памяти
	new_node->data = new_data;  // Присваиваем какое-то значение новому узлу 
	new_node->next_ptr = top;  // Создаём указатель на нашу верхушку с нового узла
	top = new_node;  // Переопределяем верхушку нашего стека на новый узел
	return;
}

void pop(Node*& top) {
	Node* current = top; // берём верхний элемент
	current = current->next_ptr; // шагаем на один вниз
	top = current;
	return;
}

void clearStack(Node*& top) {
	if (top == nullptr) {
		cout << "Стек и так пуст";
		return;
	}
	Node* current = top;
	while (current != nullptr) {
		current = current->next_ptr;
		top = current;
	}

	return;
}

int main() {
	setlocale(LC_ALL, "Russian");

	// Создаем пустой стек
	Node* head = nullptr;

	push(head, 10);
	push(head, 20);
	push(head, 30);
	printStack(head);

	pop(head);

	printStack(head);

	push(head, 40);
	push(head, 50);

	printStack(head);

	clearStack(head);

	printStack(head);

	return 0;
}