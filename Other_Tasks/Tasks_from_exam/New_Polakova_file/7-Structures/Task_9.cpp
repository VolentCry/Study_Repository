/*
Напиши программу, которая управляет массивом структур и работает с бинарным файлом.

1. Создай структуру Track. В ней должны быть поля: название трека (обязательно используй классический массив char, например char title[50], а не std::string — это критично для блочного ввода-вывода), длительность в секундах int и количество прослушиваний int.
2. Ввод данных: Создай динамический или статический массив таких структур и заполни пару элементов с клавиатуры.
3. Запись структуры в файл: Открой файл в бинарном режиме записи и запиши весь массив структур в файл одним блоком (используй функцию fwrite из <cstdio> или метод write() у объекта ofstream).
4. Чтение структуры из файла: Очисти данные в программе. Затем открой этот же файл в бинарном режиме чтения и прочитай данные обратно в массив структур с помощью блочного чтения (fread или метод read()). Выведи прочитанные треки на экран.
5. Удаление и добавление элементов: Напиши небольшую логику, которая «удаляет» один из треков из массива (например, сдвигая оставшиеся элементы влево, чтобы затереть удаляемый), а затем снова выведи обновленный список на экран.

Подсказка для экзамена: Блочный ввод-вывод (fread/fwrite или read/write) берет кусок оперативной памяти и побайтово копирует его на жесткий диск.
Именно поэтому внутри структуры нельзя использовать std::string или динамические массивы с указателями — в файл запишется только адрес памяти, а не сам текст, и при чтении программа вылетит с ошибкой.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <clocale>
using namespace std;

struct Track
{
    char title[50]; // Название трека
    unsigned play_time; // длительность трека (в секундах)
    unsigned listen_cnt; // Кол-во прослушиваний

    Track() {
        // Заполняем массив нулями (пустой строкой)
        title[0] = '\0';
        play_time = 0;
        listen_cnt = 0;
    }

    Track(string title_str, unsigned time, unsigned cnt) {
        int i = 0;
        for (i = 0; i < title_str.length(); i++) {
            title[i] = title_str[i];
        }
        title[i] = '\0';
        play_time = time;
        listen_cnt = cnt;
    }

    void print() {
        cout << endl << title << " - " << play_time << " сек. - " << listen_cnt << " listenings." << endl;
    }
};



int main() {
    setlocale(LC_ALL, "Russian");
    int N;
    cout << "Сколько треков хотите добавить? ";
    cin >> N;
    cout << endl;
    Track* track_array = new Track[N];


    // Ввод данных каждого трека
    for (int i = 0; i < N; i++) {
        cin.ignore(); // Исключаем \n в записи названия будущего трека
        string name;
        unsigned time;
        unsigned cnt;
        cout << "Трек №" << i + 1 << endl;
        cout << "Введите название трека: ";
        getline(cin, name);
        cout << "Длительность трека (в секундах): ";
        cin >> time;
        cout << "Кол-во прослушиваний: ";
        cin >> cnt;
        Track track_1(name, time, cnt);
        track_array[i] = track_1;
    }

    // Запись в структуру данных
    ofstream out_file("tracks_database.bin", ios::out | ios::binary); // Открываем файл в бинарном режиме записи (ios::out и ios::binary)

    if (out_file.is_open()) {
        // Записываем весь массив одним блоком
        out_file.write((char*)track_array, N * sizeof(Track));
        out_file.close();
    }
    // Чтение структуры из файла 
    ifstream in_file("tracks_database.bin", ios::in | ios::binary);

    if (in_file.is_open()) {
        // Читаем блок байтов обратно в массив
        in_file.read((char*)track_array, N * sizeof(Track));
        in_file.close();
    }

    // Выводим то, что прочитали
    cout << "\n--- Восстановленная база треков ---" << endl;
    for (int i = 0; i < N; i++) {
        track_array[i].print();
    }

    // Удаление элемента из структуры 
    int delete_index;
    cout << "Введите номер трека для удаления (от 1 до " << N << "): ";
    cin >> delete_index;
    delete_index--;

    if (delete_index >= 0 && delete_index < N) {
        // Сдвигаем все элементы, идущие после удаляемого, на один шаг влево
        for (int i = delete_index; i < N - 1; i++) {
            track_array[i] = track_array[i + 1];
        }

        N--; // Уменьшаем логический размер массива

        cout << "Трек успешно удален!" << endl;
    }

    // Добавление элемента
    cout << "Добавление нового элемента" << endl;
    cin.ignore(); // Исключаем \n в записи названия будущего трека
    string name;
    unsigned time;
    unsigned cnt;
    cout << "Трек №" << N + 1 << endl;
    cout << "Введите название трека: ";
    getline(cin, name);
    cout << "Длительность трека (в секундах): ";
    cin >> time;
    cout << "Кол-во прослушиваний: ";
    cin >> cnt;
    Track track_new(name, time, cnt);
    
    Track* new_track_array = new Track[N + 1];
    for (int i = 0; i < N; i++) {
        new_track_array[i] = track_array[i];
    }
    N++;
    new_track_array[N] = track_new;
    new_track_array[N].print();

    delete[] track_array, new_track_array;
    return 0;
}