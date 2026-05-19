#include<iostream>
using namespace std;

int main() {
    int N = 6, temp;
    int A[6]{3, 65, 12, 10, 43, 45};
    int minim = A[0], index = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N - i; j++) {
            if (A[j] < minim) {
                minim = A[j];
                index = j;
            }
            temp = A[i];
            A[i] = minim;
            A[index] = temp;
        }
    }
    
    for (int i = 0; i < N; i++) {
        cout << A[i] << " ";
    }
}