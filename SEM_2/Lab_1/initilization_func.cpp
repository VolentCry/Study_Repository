#include<iostream>
#include "my_structures.h"
using namespace std;


void Number::init(int a, float b) {
	first = a;
	second = b;
};


void Number::show() {
	cout << first * 1.0 + second << endl;
};

void Number::read() {
	cout << "First:  ";
	cin >> first;
	cout << "Second:  ";
	cin >> second; 
};

float Number::multipy(int k) {
	float result = (first * k) * 1.0 + second * k;
	return result;
};
