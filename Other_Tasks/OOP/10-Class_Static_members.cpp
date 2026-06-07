#include <iostream>
#include <string>
using namespace std;

/*
Статические члены класса - они создаются только для какого-то конркретного класса 
и они будут созданы в памяти программы, даже если класс ни разу не будет объявлен в коде. 
*/

class Person {

    private:
    string name;
    unsigned age;
    static inline unsigned count{}; // статическая константа

    public:
    const static inline unsigned maxAge{120}; // статическая публичная переменная
    Person(string name, unsigned age) {
        ++count;
        this->name = name;
        this->age = age;
    }

    static void printCnt() {
        // Статическая функция
        cout << "Count of persons: " << count << endl;
    }
};

int main() {
    Person man1("Tom", 19);
    Person man2("Bob", 34);
    Person man3("Ben", 10);
    Person::printCnt();
    // обращаемся к статической переменной maxAge
    cout << "Max age: " << Person::maxAge << endl;
    return 0;
}