#include <iostream>
#include <vector>
#include <cmath>
#include <clocale>

using namespace std;

const int N = 8;
int step_count = 0;
vector<vector<int>> all_solutions; // Все найденные решения

// Вспомогательная функция: печать финальной доски
void printFinalBoard(const vector<int>& board) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << (board[i] == j ? " Q " : " . ");
        }
        cout << endl;
    }
}

// Функция для печати шага (только до первого решения)
void printBoard(const vector<int>& board, int currentRow, const string& action) {
    cout << "Шаг " << ++step_count << " | " << action << " (Строка " << currentRow << "):" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i <= currentRow && board[i] == j) {
                cout << " Q ";
            }
            else {
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
        if (board[i] == col || abs(board[i] - col) == abs(i - row)) {
            return false;
        }
    }
    return true;
}

// Фаза 1: поиск первого решения с полной визуализацией каждого шага
bool solveFirst(vector<int>& board, int row) {
    if (row == N) {
        return true;
    }

    for (int col = 0; col < N; ++col) {
        if (isSafe(board, row, col)) {
            board[row] = col;
            printBoard(board, row, "Ставим ферзя");

            if (solveFirst(board, row + 1)) {
                return true;
            }

            cout << "-> Тупик! Откат: снимаем ферзя со строки " << row
                << ", столбца " << col << endl;
            cout << "------------------------" << endl;
            board[row] = -1;
        }
    }

    return false;
}

// Фаза 2: поиск всех решений (без визуализации шагов)
void solveAll(vector<int>& board, int row) {
    if (row == N) {
        all_solutions.push_back(board);
        return;
    }

    for (int col = 0; col < N; ++col) {
        if (isSafe(board, row, col)) {
            board[row] = col;
            solveAll(board, row + 1);
            board[row] = -1;
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    // --- Фаза 1: первое решение с полной трассировкой ---
    vector<int> board(N, -1);

    cout << "Начинаем поиск первого решения..." << endl;
    cout << "========================" << endl;

    if (solveFirst(board, 0)) {
        cout << "\nПервое решение найдено! Всего шагов: " << step_count << endl;
        cout << "========================" << endl;
        printFinalBoard(board);
    }
    else {
        cout << "Решение не найдено." << endl;
        return 0;
    }

    // --- Фаза 2: все решения (только финальные доски) ---
    vector<int> board2(N, -1);
    solveAll(board2, 0);

    cout << "\n========================================" << endl;
    cout << "Все решения задачи 8 ферзей (" << all_solutions.size() << " шт.):" << endl;
    cout << "========================================" << endl;

    for (int s = 0; s < (int)all_solutions.size(); ++s) {
        cout << "\nРешение #" << s + 1 << ":" << endl;
        printFinalBoard(all_solutions[s]);
    }

    return 0;
}