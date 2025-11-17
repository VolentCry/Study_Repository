#include<iostream>

using namespace std;

int main() {
    int a = 255;
    cout << "Before: " << a << endl;
    int& ref = a;
    ref++;
    cout << "After: " << a << endl; 
}