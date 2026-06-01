#include<iostream>
#include<string>
using namespace std;


class Person {
    string name;
    unsigned age{18};
    const char* profession;

public:

    void print() {
        cout << name << " " << age << " " << profession;
    }

    // Один конструктор (с значениями по умолчанию)
    Person(string person_name = "Unknown", unsigned p_age = 18, const char* prof = "-/-") {
        name = person_name;
        age = p_age;
        profession = prof;
        cout << "Person has been created!" << endl;
    }

    // Второй конструктор (без значений по умолчанию)
    Person() {
        name = "Unknown";
        age = 18;
        cout << "Person has been created without name and profession." << endl;
    }

    // Конструкторов может быть много в классе
};



int main() {
    Person man1("Alex", 29, "Seller");
    Person man2("Simon", 47, "Mechanic");
    cout << endl;
    man1.print();
    cout << endl;
    man2.print();
    cout << "\n\n";

    Person man3("Bob");
    cout << endl;
    man3.print();
}

