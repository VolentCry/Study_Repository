#include <iostream>
#include <string>
using namespace std;

class Person {
public:
    string name;
    mutable unsigned age;

    Person(string p_name, unsigned p_age) {
        name = p_name;
        age = p_age;
    }

    void print() {
        cout << name << ' ' << age << endl;
    }

    const string getName() const {
        return name;
    }

    const unsigned* getAge() const {
        return &age;
    }

    void superprint() const // Константная функция
    {
        // Может вызывать только константные функции класса!
        cout << "Это константа! Имя: " << name << " Возраст: " << age << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    const Person man1("Tom Ford", 29); // Константный объект класса
    cout << "Name: " << man1.name << endl; // Можем получать значение полей 
    // но не можем изменять
    cout << "Возраст объекта man1 до изменений: " << man1.age << endl; // Можем получать значение полей 
    man1.age++; // но так как у age есть ключевое слово mutable, то его мы можем изменять
    cout << "Возраст объекта man1 после изменений: " << man1.age << "\n\n";

    // man1.print(); - обычную функцию вызвать нельзя
    man1.superprint(); // константную функцию вызвать можно

    Person man2("Bob Builder", 43);
    man2.print();
    cout << "\n\n";
    cout << man2.getName() << endl; // На не константные объекты классов мы можем вызывать константные функции
    cout << "Получаем адрес константы: " << man1.getAge() << "\nРазадресация: " << *man1.getAge() << endl;
}