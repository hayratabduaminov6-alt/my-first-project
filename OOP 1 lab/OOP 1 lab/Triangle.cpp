#define _USE_MATH_DEFINES
#include "Triangle.h"
#include <cmath>
#include <iostream>

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

// 11) Высота, опущенная на боковую сторону
double Triangle::heightToSide() const {
    double side = sideLength();
    if (side < 1e-12) return 0.0;   // вырожденный случай
    return base * height / side;
}

// 12) Пересечение с прямой Ax + By + C = 0
bool Triangle::intersectsLine(double A, double B, double C) const {
  
    double topX = x + base / 2.0, topY = y;
    double leftX = x, leftY = y + height;
    double rightX = x + base, rightY = y + height;

    double fTop = A * topX + B * topY + C;
    double fLeft = A * leftX + B * leftY + C;
    double fRight = A * rightX + B * rightY + C;

    double eps = 1e-9;

   
    if (fTop > eps && fLeft > eps && fRight > eps) return false;
    if (fTop < -eps && fLeft < -eps && fRight < -eps) return false;

   
    return true;
}

// 2) Ввод 
istream& operator>>(istream& in, Triangle& t) {
    double x, y, b, h;
    cout << "Введите x, y (левый верхний угол): ";
    in >> x >> y;
    cout << "Введите основание и высоту: ";
    in >> b >> h;

    t.setX(x);
    t.setY(y);
    t.setBase(b);
    t.setHeight(h);

    return in;
}

// 2) Вывод 
ostream& operator<<(ostream& out, const Triangle& t) {
    out << "Треугольник: A(" << t.getX() << ", " << t.getY() << "), "
        << "основание = " << t.getBase() << ", высота = " << t.getHeight();
    return out;
}



double Triangle::area()const {
    return (base * height) / 2.0;
}

void Triangle::vozvrash(int index, double& outX, double& outY) {
    if (index == 0) {
        outX = x + base / 2.0;
        outY = y;

    }
    else if (index == 1) {
        outX = x + base;
        outY = y + height;
    }
    else if (index == 2) {
        outX = x;
        outY = y + height;
    }
    else {
        outX = 0;
        outY = 0;
    }
}
double Triangle::perimatr()const {
    return base + 2.0 * sideLength();
}


// Нахождение длины стороны (0 - основание/снизу, 1 - правая, 2 - левая)
double Triangle::getSideLength(int index) const {
    if (index == 0) {
        return base; // Снизу
    }
    else if (index == 1 || index == 2) {
        return sideLength(); // Правая и левая стороны
    }
    return 0.0; // Если индекс неверный
}




// Возврат координат заданной вершины
// 0 - верхняя, 1 - правая, 2 - левая
void Triangle::getVertex(int index, double& outX, double& outY) const {
    if (index == 0) {
        // Верхняя вершина
        outX = x + base / 2.0;
        outY = y;
    }
    else if (index == 1) {
        // Правая нижняя вершина
        outX = x + base;
        outY = y + height;
    }
    else if (index == 2) {
        // Левая нижняя вершина
        outX = x;
        outY = y + height;
    }
    else {
        // Если передан неверный индекс
        outX = 0;
        outY = 0;
    }
}

double Triangle::ploshod()const {
    return (base * height) / 2.0;
}



