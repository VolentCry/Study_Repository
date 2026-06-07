#include <iostream>
#include <string>
using namespace std;


/*
Деструктор не принимает и не возвращает никакие значения
Каждый класс может иметь только один деструктор
*/

class Person
{
private:
    string name;
    unsigned age;
    static inline unsigned count{};

public:
    Person(string name, unsigned age) {
        ++count;
        this->name = name;
        this->age = age;
        cout << "Born new human: " << name << endl;
    }

    ~Person() // Это деструктор
    { 
        --count;
        cout << "Human " << name << " die.\n";
    }

    static void showCount() {
        cout << "Count of human: " << count << endl;
    }
};

int main() 
{
    {
        cout << "Start of nested code block\n";

        Person man1("Charlie", 10);
        Person man2("Luca", 30);
        
        Person::showCount();

        cout << "End of nested code block\n";
        // Объект man1 И man2 уничтожается
    }

    Person::showCount();

    Person man3("Tom", 36);

    Person::showCount();
    
    cout << "End of programm\n";
    // Объект man3 уничтожается
}