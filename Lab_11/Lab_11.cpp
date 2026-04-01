#include<iostream>
#include<string>
#include<clocale>
using namespace std;


// Описание общей стркутуры двунаправленного спика
struct Node {
	string data;
	Node* pointer_to_prev_node = nullptr;
	Node* pointer_to_next_node = nullptr;
};

struct List {
	Node* head_node = nullptr;
	Node* tail_node = nullptr;
};


// Описание общей стркутуры стека через однонаправленный список
struct StackNode {
    int value;
    StackNode* next;
};


// Описание общей стркутуры очереди
struct QueueNode {
    int value;
    QueueNode* next;
};

struct Queue {
    QueueNode* head = nullptr;
    QueueNode* tail = nullptr;
};




// -------- Функции для работы со списком --------
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
// ------------------------------------------------


// -------- Функции для работы со стеком --------
// Функция добавления
void StackPush(StackNode*& head, int value) {
    StackNode* newNode = new StackNode{value, head};
    head = newNode;
}

// Функция удаления
void StackPop(StackNode*& head) {
    if (head == nullptr) return;
    
    StackNode* temp = head;
    head = head->next;
    delete temp;
}

// Функция чтения верхнего элемента 
int StackTop(const StackNode* head) {
    if (head == nullptr) {
        throw out_of_range("Стек пуст.");
    }
    return head->value;
}

void PrintStack(const StackNode* head) {
    if (head == nullptr) {
        cout << "Стек пуст.\n";
        return;
    }

    const StackNode* current = head; // Создаем временный указатель для прохода
    cout << "Стек (сверху вниз): ";
    
    while (current != nullptr) {
        cout << current->value << " ";
        current = current->next; // Шагаем на следующий элемент
    }
    cout << "\n";
}
// ------------------------------------------------



// -------- Функции для работы с очередью --------
void Enqueue(Queue& q, int value) {
    QueueNode* newNode = new QueueNode{value, nullptr};
    
    if (q.tail == nullptr) {
        // Если очередь была пуста, новый узел становится и Головой, и Хвостом
        q.head = newNode;
        q.tail = newNode;
    } else {
        // Если в очереди уже кто-то есть, цепляем новый узел за старым хвостом
        q.tail->next = newNode;
        // Обновляем указатель хвоста на этот новый узел
        q.tail = newNode;
    }
}

// Функция удаления из очереди
void Dequeue(Queue& q) {
    if (q.head == nullptr) return; // очередь уже пуста
    
    QueueNode* temp = q.head; // Запоминаем текущую голову
    q.head = q.head->next;    // Сдвигаем голову на следующего человека в очереди
    
    if (q.head == nullptr) {
        q.tail = nullptr;
    }
    
    delete temp; 
}

// Функция чтения первого элемента
int QueueFront(const Queue& q) {
    if (q.head == nullptr) {
        throw std::out_of_range("Очередь пуста.");
    }
    return q.head->value;
}

void PrintQueue(const Queue& q) {
    if (q.head == nullptr) {
        cout << "Очередь пуста.\n";
        return;
    }

    const QueueNode* current = q.head; // Начинаем с головы
    cout << "Очередь (от начала к концу): ";
    
    while (current != nullptr) {
        cout << current->value << " ";
        current = current->next; // Шагаем на следующий элемент
    }
    cout << "\n";
}
// ------------------------------------------------



int main() {
	setlocale(LC_ALL, "ru_RU.UTF-8");

	// ------------ РЕАЛИЗАЦИЯ СПИСКА ------------
	List test_list;
	int K;

	cout << "\nДЕМОНСТИРАЦИЯ РАБОТЫ СПИСКА\n";
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


	// ------------ РЕАЛИЗАЦИЯ СТЕКА ------------
	cout << "\nДЕМОНСТИРАЦИЯ РАБОТЫ СТЕКА\n";
	StackNode* stackHead = nullptr;

	StackPush(stackHead, 10);
	StackPush(stackHead, 20);
	StackPush(stackHead, 30);

	// Вывод всего стека
	PrintStack(stackHead);

	cout << "Верхний элемент: " << StackTop(stackHead) << "\n";

	StackPop(stackHead); // Удаляем 30
	cout << "Верхний элемент после удаления: " << StackTop(stackHead) << "\n";

	// очищаем память
	while (stackHead != nullptr) {
		StackPop(stackHead);
	}

	// ------------ РЕАЛИЗАЦИЯ ОЧЕРЕДИ ------------
	cout << "\nДЕМОНСТИРАЦИЯ РАБОТЫ ОЧЕРЕДИ\n";

	// Создаем пустую очередь
    Queue myQueue;

    Enqueue(myQueue, 10); // Встал первым
    Enqueue(myQueue, 20); // Встал вторым
    Enqueue(myQueue, 30); // Встал третьим

	// Вывод всей очереди
	PrintQueue(myQueue);

    cout << "Первый в очереди: " << QueueFront(myQueue) << "\n";

    Dequeue(myQueue);
    cout << "Первый после ухода первого: " << QueueFront(myQueue) << "\n";

    // Очистка памяти
    while (myQueue.head != nullptr) {
        Dequeue(myQueue);
    }

	return 0;
}