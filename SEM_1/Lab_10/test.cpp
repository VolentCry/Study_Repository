#include <iostream>
#include <string>
using namespace std;

int main() {
    // // Установка кодировки для корректного отображения кириллицы в консоли Windows
    setlocale(LC_ALL, "Russian");

    int N;
    cout << endl;
    cout << "Введите количество строк (N): ";
    
    if (!(cin >> N) || N <= 0) {
        cout << "Ошибка: количество строк должно быть положительным числом." << endl;
        return 1;
    }

    // // Очищаем буфер после ввода числа, чтобы функция getline не считала символ переноса строки
    // cin.ignore(10000, '\n');

    string array_of_strings[N];
    cout << "Введите строки поочередно: ";
    
    // Формируем массив строк
    for (int i = 0; i < N; ++i) {
        string temp;
        getline(cin, temp); // Считываем строку целиком, включая пробелы
        array_of_strings[i] = temp;
    }
}