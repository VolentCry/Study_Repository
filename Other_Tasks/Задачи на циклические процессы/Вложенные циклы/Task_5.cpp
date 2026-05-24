#include<iostream>
using namespace std;

int main() {
    int N, a = 1;
    cin >> N;
    if (N % 2 == 0) {
        cout << "Построение невозмонжно, так как N чётное." << endl;
        return -1;
    }

    for (int i = 1; i <= (N / 2 + 1); i++) {
        for (int x = 1; x <= (N - a) / 2; x++) {
            cout << "  ";
        }
        for (int y = 1; y <= a; y++) {
            cout << " *";
        }
        cout << endl;
        a += 2;
    }


    return 0;
}