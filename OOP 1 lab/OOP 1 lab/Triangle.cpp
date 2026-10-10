#define _USE_MATH_DEFINES
#include "Triangle.h"
#include <cmath>

using namespace std;

// 1) Конструктор по умолчанию
Triangle::Triangle() : x(0), y(0), base(2), height(3) {}

// Конструктор с аргументами
Triangle::Triangle(double x_, double y_, double base_, double height_)
    : x(x_), y(y_), base(base_), height(height_) {
}

// 3) Аксессоры
double Triangle::getX() const { return x; }
double Triangle::getY() const { return y; }
double Triangle::getBase() const { return base; }
double Triangle::getHeight() const { return height; }

void Triangle::setX(double x_) { x = x_; }
void Triangle::setY(double y_) { y = y_; }
void Triangle::setBase(double b) { base = b; }
void Triangle::setHeight(double h) { height = h; }

// 10) Длины боковых сторон
double Triangle::sideLength() const {
    return sqrt((base / 2) * (base / 2) + height * height);
}

// 4) Проверка равносторонности
bool Triangle::isEquilateral() const {
    return fabs(base - sideLength()) < 1e-9;
}

// 5) Радиус вписанной окружности
double Triangle::inRadius() const {
    double side = sideLength();
    double S = base * height / 2.0;
    double p = (base + 2 * side) / 2.0;
    return S / p;
}

// 6) Центр вписанной окружности
void Triangle::inCenter(double& cx, double& cy) const {
    cx = x + base / 2.0;
    cy = y + height - inRadius();
}

// 7) Больший угол (в радианах)
double Triangle::largerAngle() const {
    double side = sideLength();
    double cosApex = (side * side + side * side - base * base) / (2 * side * side);
    if (cosApex > 1.0)  cosApex = 1.0;
    if (cosApex < -1.0) cosApex = -1.0;
    double apexAngle = acos(cosApex);
    double baseAngle = (M_PI - apexAngle) / 2.0;
    return (apexAngle > baseAngle) ? apexAngle : baseAngle;
}

// 8) Масштабирование
Triangle Triangle::operator*(double k) const {
    return Triangle(x, y, base * k, height * k);
}

// 9) Подобие
bool Triangle::operator==(const Triangle& other) const {
    return fabs(base / height - other.base / other.height) < 1e-9;
}

// 2) Ввод
istream& operator>>(istream& in, Triangle& t) {
    cout << "Введите x, y (левый верхний угол): ";
    in >> t.x >> t.y;
    cout << "Введите основание и высоту: ";
    in >> t.base >> t.height;
    return in;
}

// 2) Вывод
ostream& operator<<(ostream& out, const Triangle& t) {
    out << "Треугольник: A(" << t.x << ", " << t.y << "), "
        << "основание = " << t.base << ", высота = " << t.height;
    return out;
}