#include<iostream>
using namespace std;

// Выводит контур квадарата из звёздочек размером N на N
int main() {
    int N;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        if (i == 1 || i == N) {
            for (int j = 1; j <= N; j++) {
                cout << "* ";   
            }   
            cout << endl;
        } else {
            cout << "* "; 
            for (int j = 1; j <= N - 2; j++) {
                cout << "  ";   
            }
            cout << "* "; 
            cout << endl;
        }
    }
    return 0;
}