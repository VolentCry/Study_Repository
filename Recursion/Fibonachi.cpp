#include <iostream>
using namespace std;    

// Рекурсивная функция для нахождения n-го числа Фибоначчи
int fibonacci(int n) {
    if (n <= 1) {
        return n; // Базовый случай: F(0)=0, F(1)=1
    }
    return fibonacci(n - 1) + fibonacci(n - 2); // Рекурсивный шаг
}

int main() {
    int n;
    cout << "Введите номер элемента (N): ";
    cin >> n;

    cout << "Последовательность до " << n << "-го номера: " << endl;
    for (int i = 0; i <= n; i++) {
        cout << fibonacci(i) << " ";
    }
    cout << endl;

    return 0;
}