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
            cout << "Точка с координатами " << x_0 << " и " << y_0 << " лежит на окружности" << endl;
		} else {
            cout << "Точка с координатами " << x_0 << " и " << y_0 << " НЕ лежит на окружности" << endl;
		}
	}
	
	return S;
}
    

int main() {
    int x, y, R;
    
    cout << "\nВведите координаты центра окружности и её радиус через пробелы: ";
    cin >> x >> y >> R;

    
    int X_0_coords [9] = {18, 2, 5, 9, 5, 1, 10, 1, 5};
    int Y_0_coords [9] = {5, 1, 8, 10, 0, 15, 2, 9, 10};
    
    cout << "Центр окружности: (" << x << ", " << y << "), Радиус: " << R << endl << endl;
    
    cout << "\n\nВызов с 3-мя параметрами";
    cout << Circle(x, y, R, 6, X_0_coords[0], Y_0_coords[0], X_0_coords[1], Y_0_coords[1], X_0_coords[2], Y_0_coords[2]) << " точек лежит на окружности." << endl;
    
    cout << "\n\nВызов с 6-ю параметрами";
    cout << Circle(x, y, R, 12, X_0_coords[0], Y_0_coords[0], X_0_coords[1], Y_0_coords[1], X_0_coords[2], Y_0_coords[2], X_0_coords[3], Y_0_coords[3], X_0_coords[4], Y_0_coords[4], X_0_coords[5], Y_0_coords[5]) << " точек лежит на окружности." << endl;

    cout << "\n\nВызов с 9-ю параметрами";
    cout << Circle(x, y, R, 18, X_0_coords[0], Y_0_coords[0], X_0_coords[1], Y_0_coords[1], X_0_coords[2], Y_0_coords[2], X_0_coords[3], Y_0_coords[3], X_0_coords[4], Y_0_coords[4], X_0_coords[5], Y_0_coords[5], X_0_coords[6], Y_0_coords[6], X_0_coords[7], Y_0_coords[7], X_0_coords[8], Y_0_coords[8]) << " точек лежит на окружности." << endl;

    return 0;
}