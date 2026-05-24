#include <iostream>

using namespace std;

int main() {
    int N = 0;
    int S = 0;
    int i = 1;
    cin >> N;
    while (i <= N) {
        S += i;
        i++;
    }
    cout << S;
}