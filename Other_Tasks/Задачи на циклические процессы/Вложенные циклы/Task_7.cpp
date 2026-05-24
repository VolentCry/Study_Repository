#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;

    if (N % 2 == 0) {
        cout << "Построение невозможно, так как N чётное." << endl;
        return -1;
    }

    // Верхняя половина + центр
    for (int i = 0; i <= N / 2; i++) {
        int stars = 2 * i + 1;

        for (int s = 0; s < (N - stars) / 2; s++) {
            cout << "  ";
        }

        for (int k = 0; k < stars; k++) {
            if (k == 0 || k == stars - 1) {
                cout << " *";
            } else {
                cout << "  ";
            }
        }
        
        cout << endl;
    }

    // Нижняя половина
    for (int i = N / 2 - 1; i >= 0; i--) {
        int stars = 2 * i + 1;

        for (int s = 0; s < (N - stars) / 2; s++) {
            cout << "  ";
        }

        for (int k = 0; k < stars; k++) {
            if (k == 0 || k == stars - 1) {
                cout << " *";
            } else {
                cout << "  ";
            }
        }

        cout << endl;
    }

    return 0;
}

