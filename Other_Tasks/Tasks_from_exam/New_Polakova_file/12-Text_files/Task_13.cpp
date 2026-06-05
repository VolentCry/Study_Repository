/*
Напиши программу-фильтр, которая анализирует текст и переносит нужные данные в другой файл.
1. Создание базы: Открой файл input.txt в режиме записи (ios::out) и запиши туда 4-5 разных строк (например, строчки из песен, названия предметов из игр — всё что угодно). Строки должны быть разной длины. Закрой этот файл.
2. Открытие потоков: Теперь открой input.txt в режиме чтения (ios::in), а новый пустой файл output.txt — в режиме записи.
3. Построчное чтение: С помощью цикла while и функции getline(in_file, str) читай исходный файл строчка за строчкой до самого конца.
4. Анализ и копирование: Для каждой прочитанной строки вычисляй её длину. Если длина строки больше 15 символов — копируй (записывай) эту строку в файл output.txt.
5. Работа с указателем (бонус для экзамена): В самом конце работы, перед закрытием файла чтения, вызови метод in_file.tellg(). Он вернет текущую позицию файлового указателя (в байтах). Так как ты дочитал файл до конца, это число будет равно общему размеру файла. Выведи его на экран!
*/

#include <iostream>
#include <fstream>
#include <string>
#include <clocale>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	ofstream in; // открытие для записи 
	ifstream out; // открытие для чтения 

	in.open("input.txt", ios::out); // Открываем файл для записи

	// Запись в файл
	if (in.is_open()) {
		in << "Hello? mum? hello dad. I'm go to school today." << endl;
		in << "The smell of freshly brewed coffee filled the cozy little kitchen." << endl;
		in << "It is raining now." << endl;
		in << "Despite the heavy rain, they decided to go for a long walk in the forest." << endl;
		in << "A sudden flash of lightning illuminated the dark night sky." << endl;
		in << "She loves to read." << endl;
		in << "Cats sleep a lot." << endl;
		in << "She carefully placed the antique vase on the top shelf of the bookcase." << endl;
	}
	in.close(); // Закрываем файл

	out.open("input.txt", ios::in); // Открываем для чтения
	in.open("output.txt", ios::out); // Открываем для записи

	string line = "";

	if (out.is_open()) {
		while (getline(out, line)) {
			if (line.length() <= 20) { // Немного переделал условие задачи
				in << line << endl;
				cout << "В файл output.txt записана строка: " << line << endl;
			}
		}
	}

	cout << "\nОбщий размер полученного файла output.txt: " << in.tellp() << endl;

	// Закрываем файлы
	in.close();
	out.close();

	return 0;
}