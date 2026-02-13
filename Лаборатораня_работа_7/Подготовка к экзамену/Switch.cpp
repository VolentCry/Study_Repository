#include<iostream>
using namespace std;

int main() {
    int a, b;
    char sign;
    cout << "Введите значение:  ";
    cin >> a >> sign >> b;
    switch(sign)
    {
        case '+': cout << a + b;
    }
}
