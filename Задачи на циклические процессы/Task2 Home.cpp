#include <iostream>
using namespace std;

// Выводит минимальный элемент последовательности, его инекс в последовательности и сколько раз он встречается
int main() {
    int N, a, min_el, S = 1, j;
    cout << "Введите общее кол-во переменных в последовательности: "; 
    cin >> N;
    cin >> min_el;
    j = 1;
    for (int i = 2; i < N + 1; ++i) {
        cin >> a;
        if (a < min_el) {
            min_el = a;
            j = i;
        } else if (a == min_el) {
            S += 1;
        }
    }
    if (S != 1) {
        cout << min_el << " " << j << " " << S;
    } else {
        cout << min_el << " " << j;
    }
    
}