/*
Напиши программу, которая демонстрирует работу обоих алгоритмов на динамических массивах.

1. Запроси у пользователя размер массива N.
2. Выдели память под два динамических массива одинакового размера.
3. Заполни первый массив случайными числами, выведи его на экран, а затем скопируй эти же значения во второй массив (чтобы мы сортировали одинаковые исходные данные).
4. Отсортируй первый массив методом выбора (Selection sort) по возрастанию.
5. Отсортируй второй массив методом вставки (Insertion sort) по возрастанию.
6. Выведи оба отсортированных массива на экран (с поясняющим текстом, какой где).
7. Корректно освободи память из-под обоих массивов.
*/

#include <iostream>
#include <clocale>
#include <cstdlib>
#include <ctime>
using namespace std;

void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
        cout << endl;
}

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    int N;
    cout << "Введите размер массива: ";
    cin >> N;
    int* d_arr_1 = new int[N];
    int* d_arr_2 = new int[N];

    for (int i = 0; i < N; i++) {
        d_arr_1[i] = rand() % 100;
        d_arr_2[i] = rand() % 100;
    }

    // Сортировка методом выбора
    cout << " --- Сортировка методом выбора --- " << endl;
    cout << "Первоначальный массив: ";
    printArray(d_arr_1, N);

    for (int i = 0; i < N - 1; i++) {
		int min = i;
		for (int j = i + 1; j < N; j++) {
			if (d_arr_1[min] > d_arr_1[j]) {
				min = j;
			}
		}
		if (min != i) {
			int temp = d_arr_1[i];
			d_arr_1[i] = d_arr_1[min];
			d_arr_1[min] = temp;
		}
	}

    cout << "Отсортированный массив: ";
    printArray(d_arr_1, N);

    // Сортировка методом вставки
    cout << " --- Сортировка методом вставки --- " << endl;
    cout << "Первоначальный массив: ";
    printArray(d_arr_2, N);

    for (int i = 1; i < N; i++) {
		for (int j = i; j > 0; j--) {
			if (d_arr_2[j] < d_arr_2[j - 1]) {
                swap(d_arr_2[j], d_arr_2[j - 1]);
			}
		}
	}

    cout << "Отсортированный массив: ";
    printArray(d_arr_2, N);

    delete[] d_arr_1;
    delete[] d_arr_2;
    return 0;
}