/*
Написать рекурсивную функцию: считывать введѐнные с клавиатуры числа до тех 
пор, пока не будет введен ноль. Составить блок-схему алгоритма и вписать код на 
С++. 
*/
#include <iostream>
#include <clocale>
using namespace std;

int input_keyboard(int n) {
    if (n == 0) {
        return 0;
    } else if (n != 0) {
        cin >> n;
        input_keyboard(n);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int a;
    cin >> a;
    input_keyboard(a);
}