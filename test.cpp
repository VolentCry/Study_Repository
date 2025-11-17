#include <iostream>
using namespace std;

int main() {
    int x = 5;
    int y = 10;
    int z = x++ + ++y;
    cout << z << endl;
}