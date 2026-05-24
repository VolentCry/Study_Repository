#include <iostream>
using namespace std;

int main() {
    // Перевернуть число
    int N, M = 0;
    cin >> N;
    while (N > 0) {
        M = M * 10 + N % 10;
        N /= 10;
    }
    cout << M << endl;
}