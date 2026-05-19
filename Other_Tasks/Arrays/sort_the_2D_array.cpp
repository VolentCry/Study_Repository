#include <iostream>
#include <cstdlib>

using namespace std;

void printMatrix(int** matrix, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

int main() {
    int N;
    cout << "Введите размер массива N (N >= 2): ";
    cin >> N;

    if (N < 2) {
        cout << "Ошибка: N должно быть не меньше 2." << endl;
        return 1;
    }

    int** matrix = new int*[N];
    for (int i = 0; i < N; ++i) {
        matrix[i] = new int[N]; 
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 100;
        }
    }

    cout << "\nИсходный массив:" << endl;
    printMatrix(matrix, N);

    for (int i = 0; i < N - 1; ++i) {
        for (int j = 0; j < N - i - 1; ++j) {
            if (matrix[1][j] > matrix[1][j + 1]) {
                for (int k = 0; k < N; ++k) {
                    int temp = matrix[k][j];
                    matrix[k][j] = matrix[k][j + 1];
                    matrix[k][j + 1] = temp;
                }
            }
        }
    }

    cout << "\nМассив, отсортированный по 2-й строке:" << endl;
    printMatrix(matrix, N);

    return 0;
}