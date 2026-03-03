#include <iostream>
#include <cstring>
#include <clocale>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    string your_string;
    string words[100]; // Максимальное количество слов
    string word;
    int word_index = 0;
    cout << "Введите строку: ";
    getline(cin, your_string);
    cout << "Вы ввели: " << your_string << endl;
    
    for (int i = 0; i < your_string.length(); i++) {
        if (your_string[i] != ',' && your_string[i] != '.' && your_string[i] != '!' && your_string[i] != '?' && your_string[i] != ';' && your_string[i] != ':' && your_string[i] != ' ') {
            word += your_string[i];
        }
        
        if (your_string[i] == ' ') {
            words[word_index] = word;
            word_index++;
            word.clear();
        }
    }

    if (word != "") {
        words[word_index] = word;
        word_index++;
    }

    string most_frequent_word = "";
    int max_count = 0;

    for (int i = 0; i < word_index; i++) {
        int current_count = 0;
        
        for (int j = 0; j < word_index; j++) {
            if (words[i] == words[j]) {
                current_count++;
            }
        }
        
        if (current_count > max_count) {
            max_count = current_count;
            most_frequent_word = words[i];
        }
    }

    cout << "\nВсего слов: " << word_index << endl;
    cout << "Самое частое слово: \"" << most_frequent_word << "\"" << endl;
    cout << "Оно встречается " << max_count << " раз(а)." << endl;

    return 0;
}