#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

class Triangle {
private:
    double x, y;      // координаты левой верхней вершины (точка A)
    double base;      // основание
    double height;    // высота

public:
    // 1) Конструктор по умолчанию
    Triangle();

    // Конструктор с аргументами
    Triangle(double x_, double y_, double base_, double height_);

    // 3) Аксессоры
    double getX() const;
    double getY() const;
    double getBase() const;
    double getHeight() const;

    void setX(double x_);
    void setY(double y_);
    void setBase(double b);
    void setHeight(double h);

    // 10) Длины боковых сторон
    double sideLength() const;

    // 4) Проверка равносторонности
    bool isEquilateral() const;

    // 5) Радиус вписанной окружности
    double inRadius() const;

    // 6) Центр вписанной окружности
    void inCenter(double& cx, double& cy) const;

    // 7) Больший угол (в радианах)
    double largerAngle() const;

    // 8) Масштабирование как операция *
    Triangle operator*(double k) const;

    // 9) Подобие как операция ==
    bool operator==(const Triangle& other) const;

    // 2) Ввод/вывод
    friend std::istream& operator>>(std::istream& in, Triangle& t);
    friend std::ostream& operator<<(std::ostream& out, const Triangle& t);
};