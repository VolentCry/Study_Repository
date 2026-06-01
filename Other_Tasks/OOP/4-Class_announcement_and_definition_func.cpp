#include <iostream>
#include<string>
using namespace std;

/*
В языке C++ можно разделять объявление и определение функций в том числе по отношению к функциям, 
которые создаются в классах. 
Для этого используется выражение имя_класса::имя_функции(параметры) { тело_функции}.
*/


class Person 
{
private:
    string name;
    unsigned age;
public:
    // Здесь обязательно оставляем прототипы функций 
    Person(string p_name, unsigned p_age); 
    void print();
};

// Мы можем вынести реализацию функции класса, в нашем случаи конструктора, за пределы самого класса 
Person::Person(string p_name, unsigned p_age)
{ 
    name = p_name; 
    age = p_age;
}

void Person:: print() 
{
    cout << "Name: " << name << "\tAge: " << age << endl;
}

int main() {
    Person man_1("Alex", 109);
    man_1.print();
}