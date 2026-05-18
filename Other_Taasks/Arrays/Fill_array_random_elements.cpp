#include<iostream>
using namespace std;

int main() {
	int array[10];
	for (int i = 0; i < 10; i++) {
		array[i] = rand()% 100 - 50;
		cout << array[i] << " ";
	}
}