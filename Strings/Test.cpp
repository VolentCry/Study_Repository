#include <iostream>
#include <clocale>
using namespace std;

#define SIZE 5 // Максимальный размер очереди

int queue[SIZE];
int front = -1;
int rear = -1;

bool isEmpty() {
    return front == -1;
}

bool isFull() {
    if ((front == 0 && rear == SIZE - 1) || (front == rear + 1)) {
        return true;
    }
    return false;
}

void printQueue() {
    if (isEmpty()) {
        cout << "Очередь пуста" << endl;
    }
    else {
        cout << "Текущая очередь: [ ";
        int i = front;
        while (i != rear) {
            cout << queue[i] << " ";
            i = (i + 1) % SIZE;
        }
        cout << queue[rear];
        cout << " ]" << endl;
    }
}

void enqueue(int value) {
    if (isFull()) {
        cout << "Очередь переполнена!" << endl;
    }
    else {
        if (front == -1) front = 0;
        rear = (rear + 1) % SIZE;
        queue[rear] = value;
        cout << "Добавлено: " << value << endl;
    }
}


void dequeue() {
    if (isEmpty()) {
        cout << "Очередь пуста!" << endl;
    }
    else {
        int removedValue = queue[front];
        if (front == rear) {
            front = -1;
            rear = -1;
        }
        else {
            front = (front + 1) % SIZE;
        }
        cout << "Удалено: " << removedValue << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    // 1. Добавляем элементы
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);

    printQueue();

    // 2. Попытка переполнения (размер 5, добавляем 6-й)
    enqueue(60);

    // 3. Удаляем элементы
    dequeue();
    dequeue();

    printQueue();

    // 4. Добавляем снова (демонстрация циклической записи в начало массива)
    enqueue(70);
    enqueue(80);

    printQueue();

    return 0;
}