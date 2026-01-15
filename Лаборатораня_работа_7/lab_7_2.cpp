#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPS = 1e-6;

double phi(double x) {
    return cos(sqrt(1.0 - 0.3 * pow(x, 3.0)));
}

int main() {
    setlocale(LC_ALL, "Russian");

    double x_current = 0.5;
    double x_next;
    double diff = 1.0;
    int step = 0;

    cout << fixed << setprecision(6);
    while (diff > EPS) {
        step++;

        x_next = phi(x_current);
        diff = abs(x_next - x_current);

        cout << "№ Шага: " << step << " Значение: " << x_next << endl;
        x_current = x_next;
    }

    cout << "\nНайденный корень: " << x_current << endl;

    return 0;
}