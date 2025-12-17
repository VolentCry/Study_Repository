#include<iostream>
using namespace std;

// Выводит квадарат из звёздочек размером N на N
int main() {
    int N;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cout << "* ";
        }
        cout << endl;
    }
    return 0;
}