#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int N = 8;
int step_count = 0;
const int MAX_VISUALIZATIONS = 4; // Количество шагов для визуализации

// Функция для печати текущего состояния доски
void printBoard(const vector<int>& board, int currentRow, const string& action) {
    cout << "Шаг " << ++step_count << " | " << action << " (Строка " << currentRow << "):" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            // Если мы находимся на заполненной строке и колонка совпадает с позицией ферзя
            if (i <= currentRow && board[i] == j) {
                cout << " Q ";
            } else {
                cout << " . ";
            }
        }
        cout << endl;
    }
    cout << "------------------------" << endl;
}

// Функция проверки: бьют ли уже поставленные ферзи клетку (row, col)
bool isSafe(const vector<int>& board, int row, int col) {
    for (int i = 0; i < row; ++i) {
        // Проверка совпадения по вертикали и диагоналям
        if (board[i] == col || abs(board[i] - col) == abs(i - row)) {
            return false;
        }
    }
    return true;
}

// Рекурсивная функция поиска решения
bool solve(vector<int>& board, int row) {
    // Базовый случай: если мы дошли до конца (поставили всех 8 ферзей)
    if (row == N) {
        return true; 
    }

    // Пробуем поставить ферзя в каждую колонку текущей строки
    for (int col = 0; col < N; ++col) {
        if (isSafe(board, row, col)) {
            board[row] = col; // Ставим ферзя

            // Визуализируем процесс постановки (первые несколько раз)
            if (step_count < MAX_VISUALIZATIONS) {
                printBoard(board, row, "Ставим ферзя");
            }

            // Рекурсивно переходим к следующей строке
            if (solve(board, row + 1)) {
                return true; // Решение найдено, выходим из рекурсии
            }
            
            // Если solve(row + 1) вернуло false, значит позиция оказалась тупиковой.
            // Происходит возврат (backtracking). Ферзь «снимается» (перезапишется на следующей итерации).
            if (step_count < MAX_VISUALIZATIONS) {
                cout << "-> Тупик! Откат со строки " << row + 1 << " назад к строке " << row << endl;
                cout << "------------------------" << endl;
            }
        }
    }
    
    // Если ни одна колонка не подошла, возвращаем false
    return false; 
}

int main() {
    // Вектор для хранения позиций. Индекс - это строка, значение - колонка (от 0 до 7)
    vector<int> board(N, -1);

    cout << "Начинаем поиск решения..." << endl;
    cout << "========================" << endl;

    if (solve(board, 0)) {
        cout << "\nФинальное решение найдено!" << endl;
        // Для финального вывода показываем доску целиком, временно сняв лимит
        step_count = -1; 
        printBoard(board, N - 1, "Итог");
    } else {
        cout << "Решение не найдено." << endl;
    }

    return 0;
}