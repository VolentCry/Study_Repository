#include <iostream>
using namespace std;

// Вводите последовательность и поллучаешь либо знак первого ненулевого элемента, либо что вся последовательность нулевая 
int main() {
    int N, a;
    bool f = false;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> a;
        if (a > 0) {
            cout << "Первый элемент последовательности положительный" << endl;
            f = true;
            break;
        } else if (a < 0) {
            cout << "Первый элемент последовательности отрицательный" << endl;
            f = true;
            break;
        }
    }
    if (!f) {
        cout << "Нулевая последовательность" << endl;
    }
}