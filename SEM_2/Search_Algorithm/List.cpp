#include <iostream>
#include <stdexcept>
#include <clocale>
using namespace std;

template <typename T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };
    Node* head;
    size_t list_size;

public:
    SinglyLinkedList() : head(nullptr), list_size(0) {}
    ~SinglyLinkedList() {
        clear();
    }
    SinglyLinkedList(const SinglyLinkedList&) = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;

    void push_front(const T& val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
        list_size++;
    }

    void push_back(const T& val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
        } else {
            Node* curr = head;
            while (curr->next) {
                curr = curr->next;
            }
            curr->next = newNode;
        }
        list_size++;
    }

    void pop_front() {
        if (empty()) {
            throw underflow_error("Список пуст");
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        list_size--;
    }

    void pop_back() {
        if (empty()) {
            throw underflow_error("Список пуст");
        }
        if (!head->next) {
            delete head;
            head = nullptr;
        } else {
            Node* curr = head;
            while (curr->next->next) {
                curr = curr->next;
            }
            delete curr->next;
            curr->next = nullptr;
        }
        list_size--;
    }

    bool remove(const T& val) {
        if (empty()) return false;

        if (head->data == val) {
            pop_front();
            return true;
        }

        Node* curr = head;
        while (curr->next && curr->next->data != val) {
            curr = curr->next;
        }

        if (curr->next) {
            Node* temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
            list_size--;
            return true;
        }
        return false;
    }

    bool find(const T& val) const {
        Node* curr = head;
        while (curr) {
            if (curr->data == val) return true;
            curr = curr->next;
        }
        return false;
    }

    size_t size() const {
        return list_size;
    }

    bool empty() const {
        return head == nullptr;
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    void print() const {
        Node* curr = head;
        while (curr) {
            cout << curr->data << " -> ";
            curr = curr->next;
        }
        cout << "nullptr\n";
    }
};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_front(5);

    cout << "Элементы списка: ";
    list.print(); // Выведет: 5 -> 10 -> 20 -> nullptr
    cout << "Размер: " << list.size() << "\n";
    list.remove(10);
    cout << "После удаления 10: ";
    list.print();
    cout << "Поиск 20: " << (list.find(20) ? "Найдено" : "Не найдено") << "\n";

    return 0;
}