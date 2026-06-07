#include <iostream>
#include <string>
using namespace std;

/*
Дружественные функции - это функции, которые не являются членами класса, 
однако имеют доступ к его закрытым членам - переменным и функциям, 
которые имеют спецификатор private.
*/

class Auto;

class Person
{
public:
    Person(string p_name)
    {
        name = p_name;
    }
    void drive(const Auto&); // Мы можем определить функцию в одном классе
 
private:
    string name;
};



class Auto {

    friend void Person::drive(const Auto&); // И потом использовать эту функцию как дружественную в другом классе
    friend void setPrice(Auto&, unsigned);

    private:
    string model;
    unsigned price;

    public:
    Auto(string name_of_car, unsigned price) {
        this->price = price;
        model = name_of_car;
    }
 
    void print() {
        cout << "Model: " << model << " Price: " << price << " $\n";
    }
};


void Person::drive(const Auto &car) {
    cout << car.model << " is driven.\n";
}

void setPrice(Auto &car, unsigned new_price) {
    car.price = new_price;
}

int main() {
    Auto car_one("Tesla", 5700);
    Person man1("Tom");
    car_one.print();
    man1.drive(car_one);
    setPrice(car_one, 5500);
    car_one.print();
}