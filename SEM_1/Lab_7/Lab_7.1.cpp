#include <iostream>
using namespace std;
struct Complex {
    double real; // Действительная часть
    double imag; // Мнимая часть
};


// 1. Функция для сложения целых чисел
int add(int a, int b) {
    return a + b;
}

// 2. Перегруженная функция для сложения комплексных чисел
Complex add(Complex a, Complex b) {
    Complex result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    return result;
}


void printComplex(Complex c) {
    cout << c.real;
    if (c.imag >= 0) {
        cout << " + " << c.imag << "i";
    } else {
        cout << " - " << -c.imag << "i";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian"); 


    int int1 = 15;
    int int2 = 25;
    int sumInt = add(int1, int2); 
    
    cout << "1. Сложение целых чисел:" << endl;
    cout << int1 << " + " << int2 << " = " << sumInt << endl << endl;

    Complex comp1 = {3.5, 2.0};  // 3.5 + 2.0i
    Complex comp2 = {1.5, -4.5}; // 1.5 - 4.5i
    Complex sumComp = add(comp1, comp2); 

    cout << "2. Сложение комплексных чисел:" << endl;
    cout << "Первое число: "; printComplex(comp1);
    cout << "Второе число: "; printComplex(comp2);
    cout << "Результат:    "; printComplex(sumComp);

    return 0;
}