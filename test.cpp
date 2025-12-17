#include<iostream>
using namespace std;

int main() {
    bool f = false;
    int a, b, i = 1;
    cin >> a;
    while (!f && a != 0) {
        cin >> b;
        if (a > b || b ==0) {
            f = true;
        } else {
            a = b;
        }
        i++;
    }
    if (b == 0) {
        cout << "Последовательность возрастает" << endl; 
    } else if (a == 0) {
        cout << "Последовательность отсутствует" << endl;
    } else {
        cout << "Последовательность не возрастает " << i << endl; 
    }
}