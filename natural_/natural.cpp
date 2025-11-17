#include <iostream>

using namespace std;

int main() {
    int N = 0;
    int S = 0;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cout << i << "\n";
        S += i;
    }
    cout << S << endl;
}