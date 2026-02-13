#include<iostream>
#include<string>
using namespace std;


int main() {
    char Z;
    int S;
    cout << "Введите искомый символ: ";
    cin >> Z;
    cout << endl;

    string N;
    cout << "Введите строку: ";
    cin >> N;
    cout << endl;
    for (int i = 0; i < N.length(); i++) {
        if (N[i] == Z) {
            S++;
        }
    }
    cout << S;
}