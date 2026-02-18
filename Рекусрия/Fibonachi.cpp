#include <iostream>
using namespace std;


unsigned long long fibonacci(int n) {
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int n;
    cout << "Введите номер числа Фибоначчи: ";
    cin >> n;

    for (int i = 0; i <= n; ++i) {
        cout << "F(" << i << ") = " << fibonacci(i) << endl;
    }

    return 0;
}