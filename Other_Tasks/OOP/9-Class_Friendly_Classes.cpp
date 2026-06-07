#include <iostream>
#include <string>
using namespace std;

class Car;

class Owner 
{
    void drive(const Car&);

public:
    string name;
    unsigned age;
    Owner(string owner_name, unsigned owner_age) {
        name = owner_name;
        age = owner_age;
    }
    
    void print() {
        cout << "Name: " << name << " Age: " << age << endl; 
    }
};



class Seller : Owner 
{
    void setPrice(Car&, unsigned);

public:
    Seller(strin name, unsigned seller_age) {
        this->name = name;
        age = seller_age;
    }
};



class Car 
{
    // Для любого класса мы можем сделать любой другой класс дружественным, то есть теперь 
    // классы Owner и Seller имеют доступ к приватным полям класса Car
    friend class Owner;
    friend class Seller;

public:
    Car(string number, string model, unsigned price) {
        this->number = number;
        this->model = model;
        this->price = price;
    }

    void showInfoAboutCar() {
        cout << model << " with number " << number ". Price: " << price << endl; 
    }
private:
    string number;
    string model;
    unsigned price;
};


void Owner::drive(const Car& car){
    cout << car.model << " with " << car.number << "is driven.\n"; 
}

void Seller::setPrice(Car& car, unsigned new_price){
    car.price = new_price;
}

int main() {
}