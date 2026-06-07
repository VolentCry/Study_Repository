#include <iostream>
#include <string>
using namespace std;


class Device
{
public:
    int power;

    Device() {
        power = 0;
        cout << "Device is created" << endl;
    }
};

class Printer : virtual public Device // Виртуальное наследование
{
public:
    Printer() {

    }
};

class Scanner : virtual  public Device  // Виртуальное наследование
{
public:
    Scanner() {

    }
};

class MFU : public Printer, public Scanner // Множественное наследование 
{
public:
    MFU() {}
}; 

int main() {
    MFU exam; // Класс Device создастя всего один раз, а если бы мы не применяли виртуальное наследование
    // то он создался бы 2 раза: один раз для  Printer, а второ раз для Scanner
    return 0;
}