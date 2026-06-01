/*
Напиши программу, которая анализирует массив с помощью отдельной функции.

1. Объявление (прототип) функции должно находиться строго до main, а Определение (само тело) функции  — после main.
2. Функция должна принимать на вход одномерный массив (любого типа) и его размер.
3. Функция должна находить сумму всех элементов массива и максимальный элемент.
4. В функцию нужно передать параметры так, чтобы она могла "вернуть" в main сразу два результата (сумму и максимум).
5. Сделай это через передачу параметров по ссылке (с помощью & в аргументах функции) или через указатели.  Внутри main вызови эту функцию, передай в нее массив, а затем выведи на экран найденную сумму и максимум.
6. Функция должна корректно завершаться (например, использовать return;, если она типа void ).
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <clocale>
using namespace std;

int arraySum(int n, int* arr, int& max_element);

void printArray(int n, int* arr) {
    for (int x = 0; x < n; x++) {
        cout << arr[x] << " ";
    }
    cout << endl;
    return;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int example_array[10] = {};
    for (int i = 0; i < 10; i++) {
        example_array[i] = rand() % 500;
    }
    cout << "Первоначальный массив: ";
    printArray(10, example_array);
    int max_el;
    int S = arraySum(10, example_array, max_el);
    cout << "Сумма элементов массива: " << S << endl << "Максимальный элемент: " << max_el;
    return 0;
}

int arraySum(int n, int* arr, int& max_element) {
    int S = 0;
    max_element = -1;
    for (int i = 0; i < n; i++) {
        S += arr[i];
        if (arr[i] > max_element) {
            max_element = arr[i];
        }
    }
    return S;
}