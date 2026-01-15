#include <iostream> 
#include <cmath> 
#include <iomanip> 

using namespace std;

const double eps = 10e-6;

double f(double x) {
	double y = acos(x) - sqrt(1.0 - 0.3 * pow(x, 3.0));
	return y;
}

double derivative(double x) {
	double y = ( -1 / (sqrt(1 - x * x)) ) + ( (9 * x * x) / (2 * sqrt(100 - 30 * pow(x, 3.0))) );
	return y;
}

int main() {
	setlocale(LC_ALL, "");

	double a = 0, b = 1;
	double x_0 = 0.7, x_1;
	int i = 1;

	x_1 = x_0 - f(x_0) / derivative(x_0);
	while (abs(x_0 - x_1) > eps) {
		x_0 = x_1;
		x_1 = x_0 - f(x_0) / derivative(x_0);
		cout << fixed << setprecision(6) << "№ Шага: " << i << " Значение: " << x_1 << endl;
		i++;
	}
	cout << fixed << setprecision(6) << x_1 << endl;
	return 0;
}