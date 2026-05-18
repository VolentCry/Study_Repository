#include<iostream>

using namespace std;

int main() {
    int a = 0;
    for (int& i = a; i < 10; i++) {
        cout << a << endl;
    }
}