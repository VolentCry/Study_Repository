#include <iostream>
#include<cstdlib>
using namespace std;

int main() {
    cout << endl << "Введите размер массива: ";
    int N;
    cin >> N;
    int arr[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            arr[i][j] = (rand()% 100);
        }
	}

    cout << endl << "Неотсортированный массив: " << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = N; i >= 0; i--) {
        int min_of_column; // Ищем минимальный элемент столбца
        for (int j = N; j >= 0; j--) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }


    return 0;
}