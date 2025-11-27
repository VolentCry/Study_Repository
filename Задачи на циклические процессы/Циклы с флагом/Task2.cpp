#include <iostream>
using namespace std;

// Минимальный элемент последовательности
int main() {
    int N, min_el, a, i = 2;
    cin >> N;
    cin >> min_el;
    while (i <= N) {
        cin >> a;
        if (a < min_el) {
            min_el = a;
        }
        i += 1;
    }
    cout << min_el;
    return 0;
}