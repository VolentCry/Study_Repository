#include<iostream>
using namespace std;

// Выводит равнобедренный прямоугольный треугольник из звёздочек с прямым углом справа вверху
int main() {
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            cout << "  ";
        }
        for (int x = 1; x <= N - i; x++) {
            cout << "* ";
        }
        cout << endl;
    }

    return 0;
}