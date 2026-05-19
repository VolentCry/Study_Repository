#include<iostream>
using namespace std;

int main() {
    int N, a;
    cin >> N;
    int A[N]{};
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < N/2; i++) {
        a = A[i];
        A[i] = A[N - 1 - i];
        A[N - 1 - i] = a;
    }

    for (int i = 0; i < N; i++) {
        cout << A[i] << " ";
    }
}