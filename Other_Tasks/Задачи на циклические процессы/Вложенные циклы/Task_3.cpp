#include<iostream>
using namespace std;

// Выводит равнобедренный прямоугольный треугольник из звёздочек с прямым углом справа внизу
int main() {
    int N;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N - i; j++) {
            cout << "  ";
        }
        for (int x = 1; x <= i; x++) {
            cout << "* ";
        }
        cout << endl;
    }

    return 0;
}