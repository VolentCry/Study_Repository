#include<iostream>
#include<string>

using namespace std;

#define CAPACITY 50000 // Size of the Hash Table
const int COLLISIONS = 0;

struct HashTableItem {
    string key;
    string value;
};


struct HashTable {
    HashTableItem** item;
    int size;
    int count;
};


// Простая, хоть и плохая, но хэш-функция
unsigned long hash_function(string str) {
    unsigned long i = 0;
    for (int j = 0; str[j]; j++)
        i += str[j];
    return i % CAPACITY;
}

int main() {
    cout << hash_function("Dima Samoilov") << endl;
    return 0;
}