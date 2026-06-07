#include <iostream>
#include <string>
using namespace std;

class Person 
{
public:
    Person(string name, unsigned short age) {
        this->name = name;
        this->age = age;
    }

    void print() const {
        cout << name << " " << age << endl;
    }
private:
    string name;
    unsigned short age;
};

class Student : public Person
{
public:
    Student(string name, unsigned short age, unsigned short grade) : Person(name, age) {
        this->grade = grade;
    }

    void print() const {
        Person::print();
        cout << grade << endl;
    }
private:
    unsigned short grade;
};

int main() {
    Person man_1("Charlie", 19);
    Student stud_1("Kim", 21, 2);
    stud_1.print();
    return 0;
}