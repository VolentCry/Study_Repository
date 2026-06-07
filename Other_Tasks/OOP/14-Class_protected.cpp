#include <iostream>
#include <string>
using namespace std;


class Person 
{
public:
    Person(string name, unsigned age) {
        this->name = name;
        this->age = age;
    }

    void print() {
        cout << name << " " << age << endl;
    }

    void Greeting() const {
        cout << "Hello. I'm " << name << " and me " << age << "years old.\n";
    }

protected: // Новый спецификатор доступа 
    string name; // Доступно из производных классов

private:
    unsigned age;
};

class Employee : private Person // public - это спецификатор доступа базового класа (по умолчанию private)
{
public:
    Employee(string name, unsigned age, string company) : Person(name, age) {
        this->company = company;
    }
    using Person::Greeting; // Разрешаем пользоваться вне зависимости от спецификаторов доступа
    void printEmployee() {
        cout << name << " work in " << company << ".\n";
        // Мы имеем доступ к переменной родителького класса (name), так как она имеет спецификатор доступа protected
    }
private:
    string company;
};


int main() {
    Person man1("Fred", 29);
    Employee emp1("Gorg", 93, "Nvidia");
    man1.print();
    emp1.printEmployee();
    emp1.Greeting();
    return 0;
}