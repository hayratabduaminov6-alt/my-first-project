#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <Windows.h>
#include <locale.h>
using namespace std;

class Triangle {
private:
    double x, y;
    double base;
    double height;

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
};

int main() {
    return 0;
}
