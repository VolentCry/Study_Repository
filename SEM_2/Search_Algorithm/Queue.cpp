#include <iostream>
#include <stdexcept>
#include <clocale>
using namespace std;

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* head; // Ссылка на начало очереди (откуда забираем)
    Node* tail; // Ссылка на конец очереди (куда добавляем)
    size_t queue_size;

public:
    Queue() : head(nullptr), tail(nullptr), queue_size(0) {}
    ~Queue() {
        clear();
    }
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    void enqueue(const T& val) {
        Node* newNode = new Node(val);
        if (empty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        queue_size++;
    }

    void dequeue() {
        if (empty()) {
            throw underflow_error("Очередь пуста");
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        queue_size--;
        if (head == nullptr) {
            tail = nullptr;
        }
    }

    T& front() {
        if (empty()) {
            throw underflow_error("Очередь пуста");
        }
        return head->data;
    }

    const T& front() const {
        if (empty()) {
            throw underflow_error("Очередь пуста");
        }
        return head->data;
    }

    size_t size() const {
        return queue_size;
    }

    bool empty() const {
        return head == nullptr;
    }

    void clear() {
        while (!empty()) {
            dequeue();
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    Queue<string> q;
    q.enqueue("Первый");
    q.enqueue("Второй");
    q.enqueue("Третий");

    cout << "Размер очереди: " << q.size() << "\n";
    cout << "Элемент в начале: " << q.front() << "\n"; // Первый

    q.dequeue();
    cout << "Элемент в начале после dequeue(): " << q.front() << "\n"; // Второй

    q.clear();
    cout << "Очередь пуста? " << (q.empty() ? "Да" : "Нет") << "\n";

    return 0;
}