#include <iostream>
using namespace std;

// Функция вывода массива
void printArray(int arr[], int size, string msg = "") {
    cout << msg;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Функция слияния двух отсортированных частей
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Создаем временные массивы
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

// Основная функция сортировки
void balancedMergeSort(int arr[], int left, int right, int& step, int size) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        cout << "\n[Шаг " << step++ << "] РАЗДЕЛЕНИЕ диапазона [" << left << "-" << right << "]" << endl;
        cout << "   Левая часть: [" << left << "-" << mid << "]" << endl;
        cout << "   Правая часть: [" << mid + 1 << "-" << right << "]" << endl;

        // Рекурсивный вызов для левой части
        balancedMergeSort(arr, left, mid, step, size);

        // Рекурсивный вызов для правой части
        balancedMergeSort(arr, mid + 1, right, step, size);

        cout << "\n[Шаг " << step++ << "] СЛИЯНИЕ: [" << left << "-" << mid << "] + [" << mid + 1 << "-" << right << "]" << endl;

        // Выводим подмассивы, которые сливаем
        cout << "   Левый подмассив: ";
        for (int i = left; i <= mid; i++) cout << arr[i] << " ";
        cout << endl;

        cout << "   Правый подмассив: ";
        for (int i = mid + 1; i <= right; i++) cout << arr[i] << " ";
        cout << endl;

        merge(arr, left, mid, right);

        // Выводим результат слияния (весь массив для наглядности)
        cout << "   Результат слияния: ";
        printArray(arr, size);
    }
}

int main() {
    setlocale(LC_ALL, "ru");

    int arr[] = { 6, 2, 3, 7, 1, 9, 5, 8, 4 };
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Исходный массив: ";
    printArray(arr, n);

    int step = 1;
    balancedMergeSort(arr, 0, n - 1, step, n);

    cout << "Итоговый массив: ";
    printArray(arr, n);

    return 0;
}

