/*
Напиши программу, которая обрабатывает введенную строку.

1. Напиши функцию, которая принимает строку как фактический параметр.
2. Задача этой функции — вывести на экран все слова из этой строки, которые не содержат букву 'А' (и 'а'). (Слова могут быть разделены пробелами).
3. В функции main реализуй ввод строки пользователем.
4. Важный теоретический момент для билета: В вопросах требуется использование функции gets().

Справка: Функция gets() считывает строку с пробелами целиком, пока не будет нажат Enter. В современных стандартах C++ (начиная с C++14) её удалили, так как она небезопасна (может вызвать переполнение буфера, если ввести слишком длинный текст).
Но раз она есть в билетах, используй её (или gets_s(), если твой компилятор будет ругаться на gets). Если совсем не скомпилируется, используй cin.getline(),
но в комментариях к коду напиши пример вызова gets(), чтобы показать преподавателю, что ты знаешь, как она работает.
*/

#include <iostream>
#include <clocale>
#include <string>
using namespace std;

void ASrings(string input_str) {
    string word;
    for (int i = 0; i < input_str.length(); i++) {
        char letter = input_str[i];
        if (letter != ' ') {
            word += letter;
        }
        else {
            bool yes = (word.find('a') == string::npos) && (word.find('A') == string::npos);
            if (!word.empty() && !yes) {
                cout << "Вывод слова: " << word << endl;
            }
            word.clear();
        }
    }
    bool yes = (word.find('a') == string::npos) && (word.find('A') == string::npos);
    if (!word.empty() && !yes) {
        cout << "Вывод слова: " << word << endl;
    }
    word.clear();
}


int main() {
    setlocale(LC_ALL, "Russian");
    string input_str;
    cout << "Введите строку: ";
    getline(cin, input_str); // Вместо метода gets
    cout << endl;
    ASrings(input_str);
}
