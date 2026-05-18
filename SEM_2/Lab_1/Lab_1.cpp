#include<iostream>
#include<my_structures.h>
using namespace std;

Number make_number(int first, float second) {
    Number temp;
    temp.init(first, second);
    return temp;
}

void main()
{
    Number A, B;
    A.init(56, 0.21);
    B.read();
}