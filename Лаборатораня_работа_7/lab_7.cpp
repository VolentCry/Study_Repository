#include<iostream>
#include <cmath>
using namespace std;

const double eps = 1e-5;

double f(double x) {
	double y = acos(x) - sqrt(1.0 - 0.3 * pow(x, 3.0));
	return y;
}
int main() {
	double a, b, c;
	cin >> a >> b;

	while ((b - a) > eps) {
		c = (a + b) / 2.0;

		if ((f(a) * f(c)) < 0) {
			b = c;
		} else {
			a = c;
		}
	}

	cout << (a + b) / 2.0 << endl;
	return 0;
}