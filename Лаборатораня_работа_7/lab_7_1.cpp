#include<iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double eps = 1e-6;

double f(double x) {
	double y = acos(x) - sqrt(1.0 - 0.3 * pow(x, 3.0));
	return y;
}

int main() {
	double a = 0, b = 1, c;

	while ((b - a) > eps) {
		c = (a + b) / 2.0;

		if ((f(a) * f(c)) < 0) {
			b = c;
		} else {
			a = c;
		}
	}

	cout << fixed << setprecision(6) << (a + b) / 2.0 << endl;
	return 0;
}