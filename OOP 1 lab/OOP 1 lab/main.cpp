#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <Windows.h>
#include <locale.h>
using namespace std;

class Triangle {
private:
    double x, y;      // координаты левой верхней вершины (точка A)
    double base;      // основание
    double height;    // высота

public:
    // 1) Конструктор по умолчанию
    Triangle() : x(0), y(0), base(2), height(3) {}

    // Конструктор с аргументами
    Triangle(double x_, double y_, double base_, double height_)
        : x(x_), y(y_), base(base_), height(height_) {
    }

    // 3) Аксессоры
    double getX() const { return x; }
    double getY() const { return y; }
    double getBase() const { return base; }
    double getHeight() const { return height; }

    void setX(double x_) { x = x_; }
    void setY(double y_) { y = y_; }
    void setBase(double b) { base = b; }
    void setHeight(double h) { height = h; }

    // 10) Длины боковых сторон
    double sideLength() const {
        return sqrt((base / 2) * (base / 2) + height * height);
    }

    // 4) Проверка равносторонности
    bool isEquilateral() const {
        return fabs(base - sideLength()) < 1e-9;
    }

    // 5) Радиус вписанной окружности
    double inRadius() const {
        double side = sideLength();
        double S = base * height / 2.0;
        double p = (base + 2 * side) / 2.0;
        return S / p;
    }

    // 6) Центр вписанной окружности
    void inCenter(double& cx, double& cy) const {
        cx = x + base / 2.0;
        cy = y + height - inRadius();
    }

    // 7) Больший угол (в радианах)
    double largerAngle() const {
        double side = sideLength();
        double cosApex = (side * side + side * side - base * base) / (2 * side * side);
        if (cosApex > 1.0)  cosApex = 1.0;
        if (cosApex < -1.0) cosApex = -1.0;
        double apexAngle = acos(cosApex);
        double baseAngle = (M_PI - apexAngle) / 2.0;
        return (apexAngle > baseAngle) ? apexAngle : baseAngle;
    }
};

int main() {
    return 0;
}