#include<iostream>
using namespace std;


int main() {
    int num_choice, N;
    cout << "Выберите фигуру:" << endl;
    cout << "1 - Квадрат\n2 - Прямоуг. тр. с углом слева внизу\n3 - Прямоуг. тр. с углом справа внизу\n4 - Прямоуг. тр. с углом слева вверху\n5 - Прямоуг. тр. с углом справа вверху" << endl;
    cin >> num_choice;
    cout << "Укажите размер: ";
    cin >> N;

    switch(num_choice) {
        case 1:
            cout << "Вы выбрали вариант 1: Квадрат" << endl;
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) {
                    cout << "* ";
                }
                cout << endl;
            }
            break;
        case 2:
            cout << "Вы выбрали вариант 2: Прямоуг. тр. с углом слева внизу" << endl;
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= i; j++) {
                    cout << "* ";
                }
                cout << endl;
            }
            break;
        case 3:
            cout << "Вы выбрали вариант 3: Прямоуг. тр. с углом справа внизу" << endl;
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N - i; j++) {
                    cout << "  ";
                }
                for (int x = 1; x <= i; x++) {
                    cout << " *";
                }
                cout << endl;
            }
            break;
        case 4:
            cout << "Вы выбрали вариант 4: Прямоуг. тр. с углом слева вверху" << endl;
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N + 1 - i; j++) {
                    cout << "* ";
                }
                cout << endl;
            }
            break;
        case 5:
            cout << "Вы выбрали вариант 5: Прямоуг. тр. с углом справа вверху" << endl;
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j < i; j++) {
                    cout << "  ";
                }
                for (int j = 1; j <= N + 1 - i; j++) {
                    cout << " *";
                }
                cout << endl;
            }
            break;
        default:
            cout << "Неверный выбор!" << endl;
            break;
    }

    return 0;
}