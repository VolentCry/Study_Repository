#include <iostream>
#include<string>
using namespace std;

class Person {
private: 
    // Мы делаем переменные имени и возраста закрытыми, инкапсулируем внутри класса  
    string name; 
    unsigned age;
public:
    Person(string person_name, unsigned p_age = 18) : name(person_name) {
        if (1 <= p_age && p_age <= 99) {
            age = p_age;
        } else {
            age = 18;
        }
    }

    void print() {
        cout << name << " " << age << endl;
    }

    // Опосредование доступа
    // Мы предоставляем возможность пользователю менять и получать пременные из поля private
    void setAge(unsigned p_age) {
        if (1 <= p_age && p_age <= 99) {
            age = p_age;
        }
    }

    string getName() {
        return name;
    }

    unsigned getAge() {
        return age;
    }

};


int main() {
    Person man_1("Alex", 109);
    man_1.print();
    
    cout << man_1.getAge() << endl;
    cout << man_1.getName() << endl;
    return 0;
}