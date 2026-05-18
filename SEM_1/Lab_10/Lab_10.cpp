#include <iostream>
#include <string>
#include <clocale>
using namespace std;

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int n;
    cout << "Введите количество строк: ";
    cin >> n;
    cin.ignore();

    string* arr = new string[n];

    for (int i = 0; i < n; i++) {
        cout << "Строка " << i + 1 << ": ";
        getline(cin, arr[i]);
    }

    if (n <= 0) {
        delete[] arr;
        return 0;
    }

    int shortestIdx = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i].length() < arr[shortestIdx].length()) {
            shortestIdx = i;
        }
    }
    
    cout << "\nУдаляем самую короткую: \"" << arr[shortestIdx] << "\"" << endl;
    string* newArr = new string[n - 1];

    for (int i = 0, j = 0; i < n; i++) {
        if (i == shortestIdx) continue;
        newArr[j] = arr[i];
        j++;
    }

    delete[] arr;
    arr = newArr;
    n--;

    cout << "\nРезультат:" << endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". " << arr[i] << endl;
    }

    delete[] arr;
    return 0;
}