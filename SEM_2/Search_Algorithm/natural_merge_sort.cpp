#include <iostream>
using namespace std;

void printArray(int arr[], int size, string msg = "") {
    cout << msg;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int findNaturalRuns(int arr[], int size, int boundaries[]) {
    int count = 0;
    int start = 0;

    for (int i = 1; i <= size; i++) {
        if (i == size || arr[i] < arr[i - 1]) {
            boundaries[count++] = i;  
            start = i;
        }
    }

    return count;  
}

void merge(int arr[], int temp[], int left, int mid, int right) {
    int i = left;    
    int j = mid;    
    int k = left;  

    while (i < mid && j < right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
        }
    }

    while (i < mid) {
        temp[k++] = arr[i++];
    }
    while (j < right) {
        temp[k++] = arr[j++];
    }

    for (int idx = left; idx < right; idx++) {
        arr[idx] = temp[idx];
    }
}

void naturalMergeSort(int arr[], int size) {
    int* temp = new int[size];  
    int boundaries[100];       
    int step = 1;

    printArray(arr, size, "Исходный массив: ");

    while (true) {
        int numRuns = findNaturalRuns(arr, size, boundaries);

        cout << "\nШаг " << step++ << endl;
        cout << "Найдено серий: " << numRuns << endl;
        cout << "Границы серий: ";
        for (int i = 0; i < numRuns; i++) {
            cout << boundaries[i] << " ";
        }
        cout << endl;

        if (numRuns == 1) {
            cout << "Массив отсортирован!" << endl;
            break;
        }

        cout << "Слияние серий:" << endl;
        int i = 0;
        while (i < numRuns - 1) {
            int left = (i == 0) ? 0 : boundaries[i - 1];
            int mid = boundaries[i];
            int right = boundaries[i + 1];

            cout << "  Сливаем [" << left << "-" << mid - 1 << "] и ["
                << mid << "-" << right - 1 << "]" << endl;

            merge(arr, temp, left, mid, right);

            printArray(arr, size, "  После слияния: ");

            i += 2;  
        }

        if (numRuns % 2 == 1) {
            cout << "  Последняя серия остается без изменений" << endl;
        }
    }

    printArray(arr, size, "Отсортированный: ");

    delete[] temp;
}

int main() {
    setlocale(LC_ALL, "ru");

    int arr[] = { 41, 9, 15, 24, 2, 1, 12, 7 };
    int n = sizeof(arr) / sizeof(arr[0]);

    naturalMergeSort(arr, n);

    return 0;
}
