#include <iostream>
#include <stack>
#include <string>
#include <clocale>
using namespace std;

bool isValid(const string& s) {
    stack<char> st;

    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        } 
        else if (c == ')' || c == '}' || c == ']') {
            if (st.empty()) {
                return false;
            }

            char top = st.top();
            st.pop();

            if ((c == ')' && top != '(') ||
                (c == '}' && top != '{') ||
                (c == ']' && top != '[')) {
                return false;
            }
        }
    }

    return st.empty();
}

int main() {
    // Примеры для проверки (оставил для наглядности)
    setlocale(LC_ALL, "ru_RU.UTF-8");
    string test1 = "()[]{}";
    string test2 = "([)]";
    
    cout << "Тест 1 (" << test1 << ") -> " << (isValid(test1) ? "Правильно" : "Ошибка") << endl;
    cout << "Тест 2 (" << test2 << ") -> " << (isValid(test2) ? "Правильно" : "Ошибка") << endl;
    cout << "--------------------------------\n";

    // Блок с пользовательским вводом
    string userInput;
    cout << "Введите вашу скобочную последовательность: ";
    cin >> userInput;

    // Проверка введенной строки и вывод результата
    if (isValid(userInput)) {
        cout << "Результат: Правильно\n";
    } else {
        cout << "Результат: Ошибка\n";
    }

    return 0;
}