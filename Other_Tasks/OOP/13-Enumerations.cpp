#include <iostream>
#include <string>
using namespace std;


// Константы перечисления принимают только целочисленные константы (int, char)
enum class Day { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
enum class Day1 { Monday = 1, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };

enum class Operations { Add = '+', Subtract = '-', Multiply = '*' };

enum class Rarity { Common = 1, Uncommon, Rare, Mythic, Legendary };
using enum Rarity; // Подключаем наше перечисление к пространству имён


int calculation(Operations oper, int a, int b) {
    // Демонстрационная функция
    switch (oper)
    {
    case Operations::Add:
        return a + b;
    case Operations::Subtract:
        return a - b;
    case Operations::Multiply:
        return a * b;
    }
};


int main() {
    // Переменные перечисления
    Day today = Day::Saturday;
    cout << "Today: " << static_cast<int>(today) << endl; // В выводе 5

    Day1 today1 = Day1::Saturday;
    cout << "Today: " << static_cast<int>(today1) << endl; // В выводе 6

    Operations oper = Operations::Multiply;
    cout << "Operations: " << static_cast<char>(oper) << endl; // В выводе *

    int result = calculation(oper, 45, 23);
    cout << "Result of calculations: " << result << endl;

    Rarity character_rarity = Uncommon;
    cout << "Raity of character = " << static_cast<int>(character_rarity) << endl;

    return 0;
}