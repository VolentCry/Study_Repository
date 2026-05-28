#include <iostream>
#include <stdexcept>
#include <clocale>
using namespace std;

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* head; // Вершина стека
    size_t stack_size;

public:
    Stack() : head(nullptr), stack_size(0) {}
    ~Stack() {
        clear();
    }
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    void push(const T& val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
        stack_size++;
    }

    void pop() {
        if (empty()) {
            throw underflow_error("Стек пуст");
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        stack_size--;
    }

    T& top() {
        if (empty()) {
            throw underflow_error("Стек пуст");
        }
        return head->data;
    }

    const T& top() const {
        if (empty()) {
            throw underflow_error("Стек пуст");
        }
        return head->data;
    }

    size_t size() const {
        return stack_size;
    }

    bool empty() const {
        return head == nullptr;
    }

    void clear() {
        while (!empty()) {
            pop();
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    Stack<double> stack;
    stack.push(1.1);
    stack.push(2.2);
    stack.push(3.3);

    cout << "Элемент на вершине: " << stack.top() << "\n"; // 3.3
    cout << "Размер стека: " << stack.size() << "\n";

    stack.pop();
    cout << "Элемент на вершине после pop(): " << stack.top() << "\n"; // 2.2

    stack.clear();
    cout << "Стек пуст? " << (stack.empty() ? "Да" : "Нет") << "\n";

    return 0;
}