#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
using namespace std;

struct Car_owner {
    char name[150]; 
    char car_number[10];
    long long phone_number;
    char technical_passport[10];
};

// Функция для добавления элемента
void writeElementToFile(const char* filename, const Car_owner& el) {
    ofstream file(filename, ios::binary | ios::app);
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл для записи!" << endl;
        return;
    }
    file.write((char*)&el, sizeof(Car_owner));
    if (!file.good()) {
        cerr << "Ошибка: сбой при записи данных в файл!" << endl;
    } else {
        cout << "Элемент '" << el.name << "' успешно записан." << endl;
    }
    file.close();
}


// Функция для удаления элемента по номеру машины
void deleteByCarNumber(const char* filename, const char* target_car_number) {
    // 1. Открываем исходный файл для чтения
    ifstream inFile(filename, ios::binary);
    if (!inFile.is_open()) {
        cerr << "Ошибка: не удалось открыть исходный файл для чтения!" << endl;
        return;
    }

    // 2. Создаем временный файл
    const char* tempFilename = "temp.bin";
    ofstream outFile(tempFilename, ios::binary);
    if (!outFile.is_open()) {
        cerr << "Ошибка: не удалось создать временный файл!" << endl;
        inFile.close();
        return;
    }

    Car_owner currentCar;
    bool found = false;

    // 3. Читаем файл блоками размером со структуру, пока он не закончится
    while (inFile.read((char*)&currentCar, sizeof(Car_owner))) {
        
        // 4. Сравниваем строки
        if (strcmp(currentCar.car_number, target_car_number) == 0) {
            found = true;
        } else {
            // Номера не совпадают, значит, сохраняем этот элемент во временный файл
            outFile.write((char*)&currentCar, sizeof(Car_owner));
        }
    }

    // 5. Обязательно закрываем файлы перед удалением
    inFile.close();
    outFile.close();

    // 6. Подменяем старый файл новым
    if (found) {
        remove(filename); // Удаляем старый файл
        rename(tempFilename, filename); // Переименовываем временный файл
        cout << "Запись с номером машины " << target_car_number << " успешно удалена." << endl;
    } else {
        remove(tempFilename); // Если ничего не удалили, просто стираем временный файл
        cout << "Машина с номером " << target_car_number << " не найдена." << endl;
    }
}


// Функция для полной очистки двоичного файла
void clearFile(const char* filename) {
    ofstream file(filename, ios::binary | ios::trunc);

    // Проверка на ошибку открытия
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << " для очистки!" << endl;
        return;
    }

    cout << "Файл " << filename << " успешно очищен." << endl;
    
    file.close();
}

// Функция для добавления двух элементов перед заданной фамилией
void addBeforeLastName(const char* filename, const char* target_last_name, const Car_owner& new_car1, const Car_owner& new_car2) {
    // 1. Открываем исходный файл для чтения
    ifstream inFile(filename, ios::binary);
    if (!inFile.is_open()) {
        cerr << "Ошибка: не удалось открыть исходный файл!" << endl;
        return;
    }

    // 2. Создаем временный файл
    const char* tempFilename = "temp.bin";
    ofstream outFile(tempFilename, ios::binary);
    if (!outFile.is_open()) {
        cerr << "Ошибка: не удалось создать временный файл!" << endl;
        inFile.close();
        return;
    }

    Car_owner currentCar;
    bool found = false;

    // 3. Читаем файл по одной структуре
    while (inFile.read((char*)&currentCar, sizeof(Car_owner))) {
        
        // 4. Если мы еще не нашли нужного человека И его фамилия есть в текущем ФИО
        if (!found && strstr(currentCar.name, target_last_name) != nullptr) {
            
            // СНАЧАЛА записываем два новых элемента
            outFile.write((char*)&new_car1, sizeof(Car_owner));
            outFile.write((char*)&new_car2, sizeof(Car_owner));
            
            found = true; // Ставим флажок, чтобы не добавить их еще раз, если встретим однофамильца
        }
        
        // ЗАТЕМ записываем текущий прочитанный элемент
        outFile.write((char*)&currentCar, sizeof(Car_owner));
    }

    inFile.close();
    outFile.close();

    // 5. Заменяем файлы, если вставка произошла
    if (found) {
        remove(filename);
        rename(tempFilename, filename);
        cout << "Два новых элемента успешно добавлены перед '" << target_last_name << "'." << endl;
    } else {
        remove(tempFilename);
        cout << "Владелец с фамилией '" << target_last_name << "' не найден. Добавление не выполнено." << endl;
    }
}


// Функция для печати (чтения) всего файла на экран
void printFile(const char* filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile.is_open()) {
        cerr << "Ошибка: не удалось открыть файл для чтения!" << endl;
        return;
    }

    Car_owner currentCar;
    int count = 1;
    
    cout << "\n--- Содержимое файла ---" << endl;
    while (inFile.read((char*)&currentCar, sizeof(Car_owner))) {
        cout << count++ << ". ФИО: " << currentCar.name 
             << " | Номер: " << currentCar.car_number 
             << " | Тел: " << currentCar.phone_number 
             << " | Паспорт: " << currentCar.technical_passport << endl;
    }
    cout << "------------------------\n" << endl;
    
    inFile.close();
}


int main() {
    const char* filePath = "C:\\Users\\Semen\\Desktop\\Programming\\c++\\study\\Study_Repository\\Lab_8\\data.bin"; 

    // 1. Очищаем файл перед началом работы (чтобы тесты не наслаивались друг на друга)
    clearFile(filePath);

    // 2. Формируем исходный файл
    cout << "[ЭТАП 1: Создание исходного файла]" << endl;
    Car_owner car_1 = {"Иванов Иван Иванович", "A123AA", 89076514371, "77BB123"};
    writeElementToFile(filePath, car_1);

    Car_owner car_2 = {"Петров Алексей Виктрович", "C519HO", 85734922007, "91AA918"};
    writeElementToFile(filePath, car_2);

    Car_owner car_3 = {"Шнуров Алексей Викторович", "C781OK", 85734572237, "10CC672"};
    writeElementToFile(filePath, car_3);

    // Выводим, чтобы посмотреть, что получилось
    printFile(filePath);

    // 3. Выполняем добавление элементов перед заданной фамилией
    cout << "[ЭТАП 2: Добавление двух машин перед 'Шнуров']" << endl;
    Car_owner new_car_1 = {"Сидоров Михаил Иванович", "B456OP", 81234567890, "11AA111"};
    Car_owner new_car_2 = {"Кузнецова Анна Сергеевна", "M789TC", 80987654321, "22BB222"};
    
    // Вызываем нашу новую функцию
    addBeforeLastName(filePath, "Шнуров", new_car_1, new_car_2);

    // Снова выводим файл, чтобы убедиться, что элементы встали куда надо
    printFile(filePath);

    // 4. Тестируем удаление (как было в вашем изначальном коде)
    cout << "[ЭТАП 3: Удаление машины с номером A123AA]" << endl;
    deleteByCarNumber(filePath, "A123AA");
    
    // Итоговый вывод
    printFile(filePath);

    return 0;
}