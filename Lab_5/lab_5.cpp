#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Введите размер массива: ";
    int N;
    cin >> N;
    
    int arr[N][N];
    cout << endl << "Исходный массив:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            arr[i][j] = rand() % 100;
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }

    int current_min = -1; 
    bool possible = true;

    for (int i = 0; i < N; i++) {
        int target_col = N - 1 - i;
        
        int best_row = -1;
        int best_val = 101;

        for (int row = 0; row < N; row++) {
            if (arr[row][target_col] > current_min && arr[row][target_col] < best_val) {
                best_val = arr[row][target_col];
                best_row = row;
            }
        }

        if (best_row != -1) {
            swap(arr[i][target_col], arr[best_row][target_col]);
            current_min = best_val; 
        } else {
            possible = false;
            break;
        }
    }

    cout << endl << "---------------------------------------" << endl;
    if (possible) {
        cout << "РЕЗУЛЬТАТ: Можно составить возрастающую диагональ." << endl;
        cout << "Массив после перестановок в столбцах:" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (j == N - 1 - i) cout << "[" << arr[i][j] << "]\t";
                else cout << arr[i][j] << "\t";
            }
            cout << endl;
        }
    } else {
        cout << "РЕЗУЛЬТАТ: Невозможно составить такую диагональ." << endl;
    }

    return 0;
}