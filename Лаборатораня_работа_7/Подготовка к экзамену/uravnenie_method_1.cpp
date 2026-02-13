#include<iostream>
#include<cmath>
using namespace std;

const double eps = 1e-6;

int equation(double x) {
    double y = acos(x) - sqrt(1 - 0.3 * pow(x, 3));
    return y;
}


int main() {
    double a = 0, b = 1, c;

    while (abs(a - b) > eps) {
        c = (a + b) / 2.0;
        equation(c)
    }
}
