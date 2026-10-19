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

// 11) Высота, опущенная на боковую сторону

double Triangle::heightToSide() const {
    double side = sideLength();
    if (side < 1e-12) return 0.0;   // вырожденный случай
    return base * height / side;
}

// 12) Пересечение с прямой Ax + By + C = 0

bool Triangle::intersectsLine(double A, double B, double C) const {
    const double eps = 1e-9;

    auto f = [&](double px, double py) { return A * px + B * py + C; };

    double xt = x + base / 2.0, yt = y;
    double xl = x, yl = y + height;
    double xr = x + base, yr = y + height;

    // Проверка пересечения отрезка (p1,p2) с прямой
    auto segIntersects = [&](double x1, double y1, double x2, double y2) -> bool {
        double f1 = f(x1, y1);
        double f2 = f(x2, y2);

        // Оба конца на прямой — отрезок лежит на прямой (пересечение)
        if (fabs(f1) < eps && fabs(f2) < eps) return true;

        // Один конец на прямой — пересечение
        if (fabs(f1) < eps || fabs(f2) < eps) return true;

        // Разные знаки — пересечение
        return (f1 > 0) != (f2 > 0);
        };

    return segIntersects(xt, yt, xl, yl) ||   // боковая левая
        segIntersects(xt, yt, xr, yr) ||   // боковая правая
        segIntersects(xl, yl, xr, yr);     // основание
}