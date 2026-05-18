#include <iostream>
#include <clocale>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    int N_1, N_2, current_line = 1;
    string line_;
    int cnt = 0;
    cout << "Введите значение N1: ";
    cin >> N_1;
    cout << "Введите значение N2: ";
    cin >> N_2;

    
    ifstream in("F1.txt");
    if (in.is_open())
    {
        while (getline(in, line_)) {
            cnt++;
        }
    }
    in.close();

    if (N_1 >= N_2) {
        cout << "Первая строка не может идти позже второй или быть такого же номера, как и вторая\n";
        return 1;
    }
    else if (N_2 - N_1 <= 1) { // Немного поправил условие (если разница 1, то между ними 0 строк)
        cout << "Между выбранными строками нет ни одной строчки\n";
        return 1;
    }
    else if (cnt < N_1) {
        cout << "В файле меньше кол-во строк, чем запрошено пользователем\n";
        return 1;
    }

    string line;
    vector<string> lines;

    ifstream in_test("F1.txt");

    if (in_test.is_open())
    {
        while (getline(in_test, line)) {
            if (N_1 < current_line && current_line < N_2 && line[0] == 'A' && line[line.size() - 1] == 'c') {
                lines.push_back(line);
            }
            current_line++;
        }
    }
    in_test.close();

    // Запись строк в файл F2.txt
    ofstream out("F2.txt", ios::trunc);

    if (out.is_open())
    {
        for (int i = 0; i < lines.size(); i++) {
            out << lines[i] << endl;
        }
    }
    out.close();

    // Подсчет слов в созданном файле F2.txt
    ifstream in_f2("F2.txt");
    int word_count = 0;
    string word;
    bool f = false;

    if (in_f2.is_open()) {
        string firstLine;

        if (getline(in_f2, firstLine)) {
            stringstream ss(firstLine);
            string word;

            while (ss >> word) {
                word_count++;
            }
        }
        in_f2.close();
    }

    cout << "Количество слов в первой строке файла F2.txt: " << word_count;

    return 0;
}