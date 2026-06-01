/*
Написать рекурсивную функцию: получение последовательности чисел 
Фибоначчи, если количество элементов в последовательности равно N. Составить 
блок-схему алгоритма и вписать код на C++.
*/
#include <iostream>
#include <clocale>
using namespace std;

int fibb(int n) {
    if (n <= 1) {
        return n;
    }
    return fibb(n - 1) + fibb(n - 2);
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int N;
    cout << "Введите значенеи N: ";
    cin >> N;
    cout << endl;
    for (int i = 0; i <= N; i++) {
        cout << fibb(i) << "\t";
    }
}