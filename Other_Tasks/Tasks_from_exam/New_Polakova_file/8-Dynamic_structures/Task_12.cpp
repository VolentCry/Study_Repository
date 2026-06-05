/*
Напиши функцию для вставки элемента в середину списка.
1. Создай функцию void insertAtPosition(Node*& head, int value, int position). position — это индекс (например, 0 — вставка в самое начало, 1 — после первого элемента и т.д.).
2. В main создай пустой список (Node* head = nullptr;), добавь пару элементов в начало, а затем вызови функцию insertAtPosition,
чтобы вставить новое число между ними. Выведи результат на экран (можешь использовать ту же функцию printQueue/printStack, переименовав её в printList).
*/

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next_ptr;
};

struct List {
    Node* head_node = nullptr;
};

void pushBack(List* list, int value) {
    Node* new_node = new Node;
    new_node->data = value;
    new_node->next_ptr = nullptr;

    if (list->head_node == nullptr) {
        list->head_node = new_node;
    }
    else {
        Node* current = list->head_node;
        
        while (current->next_ptr != nullptr) {
            current = current->next_ptr;
        }
        current->next_ptr = new_node;
    }
}

void printList(List* list) {
    if (list->head_node == nullptr) {
        cout << "Список пуст" << endl;
        return;
    }

    Node* current_node = list->head_node;
    while (current_node != nullptr) {
        cout << current_node->data << " ";
        current_node = current_node->next_ptr;
    }
    cout << endl;
}

void insertAtPosition(List* list, int value, int index) {
    int cnt = 0;
    Node* current_node = list->head_node;
    Node* new_node = new Node;
    new_node->data = value;

    if (index == 0) {
        new_node->next_ptr = list->head_node;
        list->head_node = new_node;
        return;
    }

    while (current_node != nullptr) {
        if (index - 1 == cnt) {
            new_node->next_ptr = current_node->next_ptr;
            current_node->next_ptr = new_node;
            return;
        }
        current_node = current_node->next_ptr;
        cnt++;
    }
}


int main() {
    List list;

    pushBack(&list, 100);
    pushBack(&list, 200);
    pushBack(&list, 300);

    printList(&list);

    insertAtPosition(&list, 400, 2);

    printList(&list);

    return 0;
}