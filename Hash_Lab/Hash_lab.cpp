#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <list>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <clocale>
#include <algorithm>
using namespace std;

const double A = 0.6180339887;

struct Record {
    string fio;
    string birth_date; // Формат: ДД.ММ.ГГГГ
    string phone;
    bool is_deleted = false;
};

// Преобразование строковой даты в число k для хэш-функции
long long dateToKey(const string& date) {
    string numeric_date = "";
    for (char c : date) {
        if (isdigit(c)) numeric_date += c;
    }
    if (numeric_date.empty()) return 0;
    return stoll(numeric_date);
}

// Хэш-функция: H(k) = [M (kA mod 1)]
int hashFunction(const string& key, int M) {
    long long k = dateToKey(key);
    double fractional_part = (k * A) - floor(k * A);
    return floor(M * fractional_part);
}

// Класс Хэш-таблицы (Метод цепочек)
class HashTable {
private:
    int M;
    vector<list<Record>> table;
    int collisions;

public:
    HashTable(int size) : M(size), table(size), collisions(0) {}

    void insert(const Record& rec) {
        if (rec.is_deleted) return;
        
        int index = hashFunction(rec.birth_date, M);
        
        if (!table[index].empty()) {
            collisions++;
        }
        table[index].push_back(rec);
    }

    Record* search(const string& key) {
        int index = hashFunction(key, M);
        for (auto& rec : table[index]) {
            if (rec.birth_date == key && !rec.is_deleted) {
                return &rec;
            }
        }
        return nullptr;
    }

    int getCollisions() const {
        return collisions;
    }
};

// Вспомогательные данные для генерации
const vector<string> names = {"Иванов И.И.", "Петров П.П.", "Сидоров С.С.", "Смирнов А.А.", "Кузнецов В.В."};
string generateRandomDate() {
    int d = rand() % 28 + 1;
    int m = rand() % 12 + 1;
    int y = 1970 + rand() % 35;
    string d_str = (d < 10) ? "0" + to_string(d) : to_string(d);
    string m_str = (m < 10) ? "0" + to_string(m) : to_string(m);
    return d_str + "." + m_str + "." + to_string(y);
}

string generateRandomPhone() {
    string phone = "+79";
    for (int i = 0; i < 9; ++i) phone += to_string(rand() % 10);
    return phone;
}

// Глобальный список в ОЗУ
vector<Record> ram_list;
int last_deleted_index = -1;

// 1. Генерация 100 элементов массива
void generateData() {
    ram_list.clear();
    for (int i = 0; i < 100; ++i) {
        Record rec;
        rec.fio = names[rand() % names.size()];
        rec.birth_date = generateRandomDate();
        rec.phone = generateRandomPhone();
        ram_list.push_back(rec);
    }
    cout << "[OK] Сгенерировано 100 случайных записей.\n";
}

// 2. Сохранение в файл с учетом физического удаления
void saveToFile(const string& filename) {
    int deleted_count = 0;
    for (const auto& rec : ram_list) {
        if (rec.is_deleted) deleted_count++;
    }

    if (ram_list.size() > 0 && (double)deleted_count / ram_list.size() > 0.5) {
        vector<Record> temp;
        for (const auto& rec : ram_list) {
            if (!rec.is_deleted) temp.push_back(rec);
        }
        ram_list = temp;
        last_deleted_index = -1;
        cout << "[INFO] Произведена физическая очистка удаленных записей (более 50%).\n";
    }

    ofstream out(filename);
    if (!out) {
        cout << "[ERROR] Ошибка открытия файла для записи!\n";
        return;
    }

    for (const auto& rec : ram_list) {
        out << rec.fio << ";" << rec.birth_date << ";" << rec.phone << ";" << rec.is_deleted << "\n";
    }
    out.close();
    cout << "[OK] Данные сохранены в файл: " << filename << "\n";
}

// Загрузка из файла
void loadFromFile(const string& filename) {
    ifstream in(filename);
    if (!in) {
        cout << "[ERROR] Файл не найден!\n";
        return;
    }
    ram_list.clear();
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        Record rec;
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);
        
        rec.fio = line.substr(0, pos1);
        rec.birth_date = line.substr(pos1 + 1, pos2 - pos1 - 1);
        rec.phone = line.substr(pos2 + 1, pos3 - pos2 - 1);
        rec.is_deleted = (line.substr(pos3 + 1) == "1");
        
        ram_list.push_back(rec);
    }
    in.close();
    cout << "[OK] Данные загружены из файла.\n";
}

// 3. Подсчет коллизий
void testCollisions() {
    int sizes[] = {40, 75, 90};
    cout << "\n--- Анализ коллизий ---\n";
    for (int M : sizes) {
        HashTable ht(M);
        for (const auto& rec : ram_list) {
            ht.insert(rec);
        }
        cout << "Размер хэш-таблицы: " << M << " | Коллизий: " << ht.getCollisions() << "\n";
    }
    cout << "-----------------------\n";
}

// Отображение данных
void printData() {
    cout << "\n--- Текущие записи ---\n";
    for (size_t i = 0; i < ram_list.size(); ++i) {
        if (!ram_list[i].is_deleted) {
            cout << "[" << i << "] " << ram_list[i].fio << " | " 
                 << ram_list[i].birth_date << " | " << ram_list[i].phone << "\n";
        }
    }
}

// Главное меню
int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    srand(time(NULL));
    int choice;
    string filename = "data.txt";

    while (true) {
        cout << "\n=== МЕНЮ ===\n"
             << "1. Сгенерировать 100 элементов (ДСЧ)\n"
             << "2. Загрузить из файла\n"
             << "3. Сохранить в файл\n"
             << "4. Вывести данные на экран\n"
             << "5. Добавить элемент\n"
             << "6. Удалить элемент (Логически)\n"
             << "7. Отменить последнее удаление\n"
             << "8. Поиск по ключу (Дата рождения) через Хэш-таблицу\n"
             << "9. Подсчитать коллизии (Размеры 40, 75, 90)\n"
             << "0. Выход\n"
             << "Ваш выбор: ";
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
            case 1:
                generateData();
                break;
            case 2:
                loadFromFile(filename);
                break;
            case 3:
                saveToFile(filename);
                break;
            case 4:
                printData();
                break;
            case 5: {
                Record rec;
                cout << "ФИО: "; cin.ignore(); getline(cin, rec.fio);
                cout << "Дата рождения (ДД.ММ.ГГГГ): "; cin >> rec.birth_date;
                cout << "Телефон: "; cin >> rec.phone;
                
                int pos_choice;
                cout << "Куда добавить? (1-Начало, 2-Конец, 3-По индексу): ";
                cin >> pos_choice;
                
                if (pos_choice == 1) ram_list.insert(ram_list.begin(), rec);
                else if (pos_choice == 2) ram_list.push_back(rec);
                else {
                    int idx; cout << "Индекс: "; cin >> idx;
                    if (idx >= 0 && idx <= ram_list.size()) 
                        ram_list.insert(ram_list.begin() + idx, rec);
                    else cout << "Неверный индекс!\n";
                }
                break;
            }
            case 6: {
                int del_choice;
                cout << "Удалить по: 1-Индексу, 2-Ключу(Дата рождения): ";
                cin >> del_choice;
                
                if (del_choice == 1) {
                    int idx; cout << "Введите индекс: "; cin >> idx;
                    if (idx >= 0 && idx < ram_list.size() && !ram_list[idx].is_deleted) {
                        ram_list[idx].is_deleted = true;
                        last_deleted_index = idx;
                        cout << "[OK] Запись логически удалена.\n";
                    } else cout << "Ошибка индекса или запись уже удалена.\n";
                } else {
                    string key; cout << "Введите дату рождения: "; cin >> key;
                    bool found = false;
                    for (size_t i = 0; i < ram_list.size(); ++i) {
                        if (ram_list[i].birth_date == key && !ram_list[i].is_deleted) {
                            ram_list[i].is_deleted = true;
                            last_deleted_index = i;
                            found = true;
                            cout << "[OK] Запись логически удалена.\n";
                            break; 
                        }
                    }
                    if (!found) cout << "Запись не найдена.\n";
                }
                break;
            }
            case 7: {
                if (last_deleted_index != -1 && ram_list[last_deleted_index].is_deleted) {
                    ram_list[last_deleted_index].is_deleted = false;
                    cout << "[OK] Удаление записи отменено.\n";
                    last_deleted_index = -1;
                } else {
                    cout << "Нет операций для отмены или структура была очищена.\n";
                }
                break;
            }
            case 8: {
                string key;
                cout << "Введите дату рождения для поиска (ДД.ММ.ГГГГ): ";
                cin >> key;
                
                // Строим таблицу "на лету" из ОЗУ для поиска
                HashTable ht(90); // Выбираем оптимальный размер
                for (const auto& rec : ram_list) ht.insert(rec);
                
                Record* result = ht.search(key);
                if (result) {
                    cout << "\n[НАЙДЕНО] " << result->fio << " | " << result->birth_date << " | " << result->phone << "\n";
                } else {
                    cout << "\n[ОШИБКА] Запись с таким ключом не найдена.\n";
                }
                break;
            }
            case 9:
                testCollisions();
                break;
            default:
                cout << "Неверный ввод.\n";
        }
    }
    return 0;
}