#include<iostream>

using namespace std;

int main() {
    // Указатели
    cout << "Указатели" << endl;

    int num = 23;
    int * p = &num;
    cout << num << " " << p << endl;
    int t = *p;
    cout << t << endl;
    cout << *p << endl;
    cout << &t << endl;
    cout << *&t << endl;


    // Ссылки
    cout << "\nСсылки" << endl;

    int a = num;
    int&q = a;
    cout << q << endl;
    a = 45;
    cout << q << endl;
    a = *p;
    cout << q << endl;
}