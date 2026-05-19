#include <iostream>
#include <vector>
#include <algorithm> // для std::swap

// Вспомогательная функция для вывода вектора
void printVector(const std::vector<int>& vec) {
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// 1. Сортировка пузырьком (Bubble Sort)
void bubbleSort(std::vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false; // Оптимизация
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // Если обменов не было, массив уже отсортирован
        if (!swapped) break;
    }
    std::cout << "Пузырьком: ";
    printVector(arr);
}

// 2. Сортировка выбором (Selection Sort)
void selectionSort(std::vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(arr[i], arr[min_idx]);
        }
    }
    std::cout << "Выбором:   ";
    printVector(arr);
}

// 3. Сортировка вставками (Insertion Sort)
void insertionSort(std::vector<int> arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Сдвигаем элементы, которые больше key, на одну позицию вперед
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    std::cout << "Вставками: ";
    printVector(arr);
}

int main() {
    // Исходные данные
    std::vector<int> data = {64, 34, 25, 12, 22, 11, 90};

    std::cout << "Исходный массив: ";
    printVector(data);
    std::cout << "------------------" << std::endl;

    // Запускаем сортировки (передаем по значению, чтобы не портить оригинал для других тестов)
    bubbleSort(data);
    selectionSort(data);
    insertionSort(data);

    return 0;
}
