#include <iostream>
#include <string>
using namespace std;

class Person {
private:
    string name;
    unsigned age;
public:
    Person(string p_name, unsigned p_age) {
        name = p_name;
        age = p_age;
    }

    Person(const Person &p) { // Ручное объявление конструктора копирования
        name = p.name; 
        age = p.age + 1;
    }
    // Person(const Person &p) = delete; // Убирает у класса конструкттор копирования

    void print() {
        cout << name << " " << age << endl;
    }

};

int main() {
    Person man1("Tomas", 19);
    man1.print();
    Person double_man(man1); //  Копируем поля объекта man_1
    double_man.print();
}