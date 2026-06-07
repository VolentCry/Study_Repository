#include <iostream>
#include <string>
using namespace std;

class Camera
{
public:
    Camera(unsigned short camera_mpi) {
        mpi = camera_mpi;
    }

    void ShowInfo() {
        cout << "Camera with " << mpi << " mpi\n";
    }

    void makePhoto(unsigned short cnt) {
        cout << "You maked " << cnt << " photos.\n";
    }

private:
    unsigned short mpi;

};

class Phone
{
public:
    Phone(string your_number) {
        number = your_number;
    }

    void makeCall(string number) {
        cout << "You call to number: " << number << endl;
    }

    void ShowInfo() {
        cout << "Your number: " << number << endl;
    }

private:
    string number;

};

class Smartphone : public Camera, public Phone 
{
public:
    Smartphone(string your_number, string model, string operation_system, unsigned short camera_mpi) : Camera(camera_mpi), Phone(your_number)
    {
        this->model = model;
        OS = operation_system;
    }

    void ShowInfo() {
        cout << "=== Your phone infomation ===\nModel: " << model << "\nOperation system: " << OS << endl;
        Phone::ShowInfo();
        Camera::ShowInfo();
        cout << endl;
    }
    
private:
    string model;
    string OS;
};

int main() {
    Smartphone phone_1("+79194804030", "Realme 16 Pro", "Android", 128);
    phone_1.ShowInfo();
    phone_1.makeCall("+79125823566");
    phone_1.makePhoto(5);
    return 0;
}