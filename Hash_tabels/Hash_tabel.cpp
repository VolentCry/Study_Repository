#include<iostream>
using namespace std;

#define CAPACITY 50000 // Size of the Hash Table

unsigned long hash_function(char* str) {
    unsigned long i = 0;
    for (int j=0; str[j]; j++)
        i += str[j];
    return i % CAPACITY;
}

int main() {
    cout << hash_function("Dima") << endl;
    return 0;
}