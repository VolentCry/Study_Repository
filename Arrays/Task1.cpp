#include<iostream>
using namespace std;

int main() {
    int N, S = 0, a = 0, maxim;
    cin >> N;
    int A[N]{};
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    maxim = A[0];
    for (int i = 1; i < N; i++) {
        if (A[i] > maxim) {
            a = i;
            maxim = A[i];
        }
    }
    for (int i = 0; i < N; i++) {
        if (A[i] == maxim) {
            S += 1;
        }
    }

    cout << "Muximum: " << maxim << " Index: " << a << " Number: " << a + 1 << " Cnt: " << S;
}