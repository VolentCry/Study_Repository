#include <iostream>
using namespace std;

int main() {
    int a = 5, b = 7;
    int *pa = &a, *pb = &b;
    cout << pa << " " << pb << endl;
    cout << *pa << " " << *pb << endl;
}