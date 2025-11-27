#include <iostream>
using namespace std;

// Поиск цифры Z в числе N
int main() {
    int N, Z;
    bool f = false;
    cin >> N;
    cin >> Z;
    while (N > 0 && !f) {
        if (Z == N % 10) {
            f = true;
        }
        N /= 10;
    }
    if (f) {
        cout << "Цифра Z встречается в числе N." << endl;
    } else {
        cout << "Цифра Z не встречается в числе N." << endl;
    }
    return 0;
}