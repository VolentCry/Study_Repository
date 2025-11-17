#include<iostream>

using namespace std;

int main() {
    int a = 1, b = 2, c = 3;
    int* p_1 = &a, *p_2 = &c;
    int** pp = &p_1;

    cout << pp << " " << *pp << " " << **pp << endl;
    p_1 = &b;
    cout << pp << " " << *pp << " " << **pp << endl;
    pp = &p_2;
    cout << pp << " " << *pp << " " << **pp << endl;
}