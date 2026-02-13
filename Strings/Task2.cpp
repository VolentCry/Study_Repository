#include<iostream>
#include<string>
using namespace std;


int main() {
    string N;
    cout << "Введите строку: ";
    cin >> N;
    for (int i = 0; i < N.length(); i++) {
        if (N[i] == 'a') {
            N.erase(i, 1);
            i--;
        }
    }
    cout << N;
}