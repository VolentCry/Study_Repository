#include <iostream>
using namespace std;


int fibonacci(int n) {
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int n;
    int S = 0;
    cout << "Введите номер числа Фибоначчи: ";
    cin >> n;

    for (int i = 0; i <= n; ++i) {
        int fibonacci_number = fibonacci(i);
        S += fibonacci_number;
        cout << "F(" << i << ") = " << fibonacci_number << endl;
    }
    cout << S;

    return 0;
}