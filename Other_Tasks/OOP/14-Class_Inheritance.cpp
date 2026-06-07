#include <iostream>
#include <string>
using namespace std;

// Если после Person написать ключевое словов final, то это запретит наследование
class Person 
{
public:
    Person(string name, unsigned age) {
        this->name = name;
        this->age = age;
    }

    Person (const Person &person) // Конструктор копирования
    {
        name = person.name;
        age = person.age;
    }

    ~Person() {
        cout << "Human is die.\n";
    }

    void Greeting() {
        cout << "Hello! I'm " << name << " and me " << age << " years old.\n";
    }

private:
    string name;
    unsigned age;
};

class Student : public Person 
{
public:
    Student(string name, unsigned age, unsigned grade) : Person(name, age) {
        this->grade = grade;
    }

    Student (const Student &student) : Person(student) // Вызываем конструктор копирования базавого класса
    {
        grade = student.grade;
    }

    using Person::Person; // Подключение конструктора базового класса

    int GetGrade() {
        return this->grade;
    }

private:
    unsigned grade;
};


int main() {
    Person man1("Tom", 19);
    Student student_1("Ben", 21, 2);
    Student student_2("Hopps", 18);
    Student student_3(student_1);
    man1.Greeting();
    student_1.Greeting();
    student_2.Greeting();
    student_3.Greeting();

    cout << "\nStudent 2 Grade = " << student_1.GetGrade() << "\tStudent 3 Grade = " << student_3.GetGrade() << endl;
    return 0;
}