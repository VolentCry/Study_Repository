#include <iostream>
using namespace std;

class Point {
private:
    float x_coord;
    float y_coord;
public:
    Point(float x_coord, float y_coord) {
        this->x_coord = x_coord;
        this->y_coord = y_coord;
    }

    void showCoords() {
        cout << "Point X: " << this->x_coord << " Y: " << y_coord << endl;
    }

    Point& move(float x, float y) {
        x_coord += x;
        y_coord += y;
        return *this; // С помощью ключевого слова this можно возвращть текущей объект класса 
    }

    Point* move2(float x, float y) {
        // Альтернативный вариант функции выше
        x_coord += x;
        y_coord += y;
        return this;
    }
};

int main() {
    Point p1(10.293, 12.3332);
    p1.showCoords();
    p1.move(10.22, 5.1123).move(10.1, 10.0101055); // такие мувы мы можем делать благодаря ключевому слову this
    p1.showCoords();

    // Альтернативный аналогичный вариант
    cout << endl;
    Point p2(10.293, 12.3332);
    p2.showCoords();
    p2.move2(10.22, 5.1123)->move2(10.1, 10.0101055); // такие мувы мы можем делать благодаря ключевому слову this
    p2.showCoords();
    return 0;
}