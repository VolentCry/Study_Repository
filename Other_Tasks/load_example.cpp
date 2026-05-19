#include<iostream>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    
    cout << "Загрузка..." << flush;
    this_thread::sleep_for(chrono::seconds(10));
    cout << "\rГотово!    " << endl;
    return 0;
}
