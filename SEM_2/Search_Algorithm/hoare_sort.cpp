#include <iostream>
#include <vector>
#include <utility>
#include <clocale>
using namespace std;

// Функция разделения по схеме Хоара
int partitionHoare(vector<int>& arr, int low, int high) {
    // В качестве опорного элемента выбираем средний элемент
    int pivot = arr[low + (high - low) / 2];
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);
        do {
            j--;
        } while (arr[j] > pivot);
        if (i >= j) {
            return j;
        }
        swap(arr[i], arr[j]);
    }
}

void quickSortHoare(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionHoare(arr, low, high);
        quickSortHoare(arr, low, pi);
        quickSortHoare(arr, pi + 1, high);
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
    cout << "Исходный массив (Hoare): ";
    printArray(arr);
    quickSortHoare(arr, 0, arr.size() - 1);
    cout << "Отсортированный массив: ";
    printArray(arr);
    return 0;
}