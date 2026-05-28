#include <iostream>
#include <vector>
#include <utility>
#include <clocale>
using namespace std;

// Функция разделения по схеме Ломуто
int partitionLomuto(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; 
    int i = low - 1; // Индекс границы меньших элементов

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}


void quickSortLomuto(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionLomuto(arr, low, high);
        quickSortLomuto(arr, low, pi - 1);
        quickSortLomuto(arr, pi + 1, high);
    }
}

void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << "\n";
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    vector<int> arr = {10, 7, 8, 9, 1, 5, -3, 2, 8};
    cout << "Исходный массив (Lomuto): ";
    printArray(arr);
    quickSortLomuto(arr, 0, arr.size() - 1);
    cout << "Отсортированный массив: ";
    printArray(arr);
    return 0;
}