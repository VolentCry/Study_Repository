#include <iostream>
#include <cmath>
#include <cstdarg>
using namespace std;

/*
Написать функцию circle с переменным количесвтом параметров, которая вычисляет принадлежит
ли точка окружности. Координаты центра окружности и её радиус задаются один раз в 
начале программы. Координаты точек задаются последовательно. Функцию circle мы вызываем не
меньше трёх раз с 3, 6, 9 параметрами
*/


int Circle(int x, int y, int R, int cnt, ...) {
    int S = 0;
    va_list coords;
    va_start(coords, cnt);
    
    for (int i = 0; i < cnt / 2; i++) {
        int x_0 = va_arg(coords, int);
        int y_0 = va_arg(coords, int);
		bool isIn = (pow((x - x_0), 2) + pow((y - y_0), 2)) == pow(R, 2);
		if (isIn) {
		    S += 1;
		}
	}
	
	return S;
}
    

int main() {
    int x, y, R;
    
    // cout << "Введите координаты центра окружности и её радиус через пробелы: ";
    cin >> x >> y >> R;
    if (!(cin >> x >> y >> R)) return 1;
    
    int X_0_coords [18] = {5, 6, 1};
    int Y_0_coords [18] = {7, 0, 1};
    
    cout << Circle(x, y, R, 6, X_0_coords[0], Y_0_coords[0], X_0_coords[1], Y_0_coords[1], X_0_coords[2], Y_0_coords[2]) << endl;
    
    return 0;
}