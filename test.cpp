#include<iostream>
using namespace std;

void Replace(int* tA, int* tB) {
    int temp = *tA;
    *tA = tB;
    *tB = tA;
}

int main() {
    int a = 6, int b = 79;
    cout << a, b;

    Replace(&a, &b);

    cout << a, b;
}