#include <iostream>
using namespace std;

int main() {
    int S = 0, N;
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        int p = 1;
        for (int j = i; j <= 2*i; ++j) {
            p *= j;
        }
        S += p;
    }
    cout << S << endl;
    return 0;
}
