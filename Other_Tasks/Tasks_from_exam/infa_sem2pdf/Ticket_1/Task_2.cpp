/*
Текстовые файлы: написать на C++ функцию, копирующую в файл F2 только те 
строки из F1, которые начинаются и заканчиваются на одну и ту же букву.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <clocale>
#include <cctype>
using namespace std;

int main() {
    string line; // Для чтения строк
    ifstream in("C:\\Users\\Semen\\Desktop\\Programming\\c++\\study\\Study_Repository\\Other_Tasks\\Tasks_from_exam\\infa_sem2pdf\\Ticket_1\\F2.txt"); // Открытие файла для чтения 
    ofstream out("C:\\Users\\Semen\\Desktop\\Programming\\c++\\study\\Study_Repository\\Other_Tasks\\Tasks_from_exam\\infa_sem2pdf\\Ticket_1\\F1.txt"); // Открывает поток для записи 
    if (in.is_open()) { // Проверяем, что файл открыт
        while (getline(in, line)) {
            bool a = tolower(line[0]) == tolower(line[line.length() - 1]);
            if (a) {
                out << line << endl;
            }

        }
    }
    in.close();
    out.close();
    cout << "Done!";
}

