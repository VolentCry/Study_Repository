#include<iostream>
#include<cstdarg>

using namespace std;


int sum(int cnt, ...) {
	int S = 0;
    va_list numbers;
    va_start(numbers, cnt);

    for (int i = 0; i < cnt; i++) {
        S += va_arg(numbers, int);
    }

    va_end(numbers);

	return S;
}


int main() {
	cout << sum(500, 857, 26, 57, 234, 10, 965, 9494) << endl;
	
	return 0;
}


