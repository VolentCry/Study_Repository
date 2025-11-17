#include <iostream>
using namespace std;

int main() {
    int a, b;
    char oper;
    cin >> a >> oper >> b;
    switch (oper)
    {
        case '+':
            cout << a << " " << oper << " " << b << " = " << a + b << "\n";
            break;
        case '-':
            cout << a << " " << oper << " " << b << " = " << a - b << "\n";
            break;
        case '*':
            cout << a << " " << oper << " " << b << " = " << a * b << "\n";
            break;
        case '/':
            if (b == 0) {
                return -1; 
            } else {
                float result =  a / b;
                cout << a << " " << oper << " " << b << " = " << result << "\n";
                break;
            }
        default:
            break;
    }
}