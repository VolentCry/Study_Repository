#include <iostream>
#include <vector>
#include <clocale>
using namespace std;

// сортировка Шелла
void shellSort(vector<int>& arr) {
    int n = arr.size();

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            // Сдвигаем элементы, которые больше temp, на шаг вперед,
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            // Помещаем сохраненный элемент temp на его правильное место
            arr[j] = temp;
        }
    }
}

void printArray(const vector<int>& arr) {
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    vector<int> arr = {12, 34, 54, 2, 3, -5, 0, 8, 11};
    cout << "Исходный массив: ";
    printArray(arr);
    shellSort(arr);
    cout << "Отсортированный массив: ";
    printArray(arr);
    return 0;
}