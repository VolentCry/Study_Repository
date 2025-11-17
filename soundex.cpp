#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string start_word = "";
    cin >> start_word;

    string new_word = start_word.substr(0, 1); // Сохраняем начальный символ слова

    // vector<string> data = {"a", "e", "h", "i", "o", "u", "w", "y"};
    // for (size_t i = 0; i != data.size(); ++i) {
    //     std::cout << data[i] << " ";
    //     if (start_word.find(data[i]) < 21) {
    //         start_word.erase(start_word.begin());
    //     }
    // }
    cout << start_word.front() << "\n";
    cout << new_word << " " << start_word << "\n";
}