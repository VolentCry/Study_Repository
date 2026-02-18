#include <iostream>
#include <cmath>
#include <iomanip>
#include <numbers>

using namespace std;

const double PI = acos(-1.0);


double exact_function(double x) {  
    return (PI * PI / 8.0) - (PI / 4.0) * abs(x);
}

// Функция для вычисления суммы ряда S(x) для заданного n
double series_sum(double x, int n) {
    double sum = 0.0;
    for (int i = 1; i <= n; ++i) {
        // Формируем знаменатель и аргумент косинуса: (2n - 1)
        double term_base = 2.0 * i - 1.0; 
        // Добавляем текущий член ряда к общей сумме
        sum += cos(term_base * x) / (term_base * term_base);
    }
    return sum;
}

int main() {
    // Настройка вывода русских символов (для Windows)
    setlocale(LC_ALL, "Russian");

    double a = PI / 5, b = PI;
    int n = 40, k = 10;

    // Вычисляем шаг
    double step = (b - a) / k;

    // Настройка форматированного вывода таблицы
    cout << fixed << setprecision(5);
    cout << "\n----------------------------------------------------------\n";
    cout << setw(10) << "x" << " | " 
         << setw(12) << "Точное y(x)" << " | " 
         << setw(12) << "Ряд S(x)" << " | " 
         << setw(12) << "Погрешность" << "\n";
    cout << "----------------------------------------------------------\n";

    // Цикл от a до b включительно. 
    // Используем k+1 итераций, чтобы точно захватить правую границу b
    for (int i = 0; i <= k; ++i) {
        double x = a + i * step;
        
        double y_exact = exact_function(x);
        double s_approx = series_sum(x, n);
        double error = abs(y_exact - s_approx);

        // Выводим строку таблицы
        cout << setw(10) << x << " | " 
             << setw(12) << y_exact << " | " 
             << setw(12) << s_approx << " | " 
             << setw(12) << error << "\n";
    }
    cout << "----------------------------------------------------------\n";

    return 0;
}