#include <iostream>
using namespace std;

// Выводит максимальный элемент последовательности, его инекс в последовательности и сколько раз он встречается
int main() {
    int N, a, max_el, S = 1, j;
    cout << "Введите общее кол-во переменных в последовательности: "; 
    cin >> N;
    cin >> max_el;
    j = 1;
    for (int i = 2; i < N + 1; ++i) {
        cin >> a;
        if (a > max_el) {
            max_el = a;
            j = i;
            S = 1;
        } else if (a == max_el) {
            S += 1;
        }
    }
    if (S != 1) {
        cout << max_el << " " << j << " " << S;
    } else {
        cout << max_el << " " << j;
    }
    
}