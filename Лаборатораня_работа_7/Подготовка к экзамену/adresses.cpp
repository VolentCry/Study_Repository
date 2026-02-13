#include<iostream>
using namespace std;

int main() {
    int a = 7;
    int *p_a = &a;
    int **P_a = &p_a;
    cout << a << " " << p_a << " " << P_a << endl;
    
    for (int i = 0; i <= 5; i++) {
        ++*p_a;
    }

    cout << a << endl;

    int c, d = 9;
    int* p_c = &c;
    *p_c = d;
    cout << c;
}
