#include<iostream>
#include<string>
using namespace std;


class Person {
    const string name; // теперь это КОНСТАНТА!!!
    unsigned age;

public:

    void print() {
        cout << name << " " << age << endl;
    }

    Person(string person_name = "Unknown", unsigned p_age = 18) : name{person_name} { // После двоеточия это список инициализации, нужен в первую очередь для констант
        age = p_age;
        cout << "Person has been created!" << endl;
    }

    // Спсики инициализации применимы и к обычным параметрам
    //     Person(string person_name = "Unknown", unsigned p_age = 18) : name{person_name}, age{p_age} { 
    // }
};



int main() {
    Person man1("Alex", 29);
    man1.print();
}

