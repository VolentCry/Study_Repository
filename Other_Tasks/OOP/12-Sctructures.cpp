#include <iostream>
#include <string>
using namespace std;

/*
Любой класс можно представить в виде структуры и наоборот
*/

struct person
{
    unsigned age;
    string name;
};
 
int main()
{
    person tom;
    tom.name = "Tom";
    tom.age = 34;
    cout << "Name: " << tom.name << "\tAge: " << tom.age << endl;
    person bob{14, "Bob"};
    cout << "Name: " << bob.name << "\tAge: " << bob.age << endl;
}