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

    // 8) Масштабирование как операция *
    Triangle operator*(double k) const {
        return Triangle(x, y, base * k, height * k);
    }

    // 9) Подобие как операция ==
    bool operator==(const Triangle& other) const {
        return fabs(base / height - other.base / other.height) < 1e-9;
    }

    // 2) Ввод
    friend istream& operator>>(istream& in, Triangle& t) {
        cout << "Введите x, y (левый верхний угол): ";
        in >> t.x >> t.y;
        cout << "Введите основание и высоту: ";
        in >> t.base >> t.height;
        return in;
    }

    // 2) Вывод
    friend ostream& operator<<(ostream& out, const Triangle& t) {
        out << "Треугольник: A(" << t.x << ", " << t.y << "), "
            << "основание = " << t.base << ", высота = " << t.height;
        return out;
    }


   
};


int main() {


    // ===== 1) КОНСТРУКТОРЫ =====
    cout << "1) Конструктор по умолчанию: ";
    Triangle t1;
    cout << t1 << endl;

    cout << "1) Конструктор с аргументами: ";
    Triangle t2(0, 0, 4, 3);
    cout << t2 << endl << endl;

    // ===== 4) РАВНОСТОРОННОСТЬ =====
    cout << "4) t2 равносторонний? " << (t2.isEquilateral() ? "да" : "нет") << endl;

    Triangle t3(0, 0, 2, sqrt(3.0));
    cout << "4) t3 = " << t3 << endl;
    cout << "4) t3 равносторонний? " << (t3.isEquilateral() ? "да" : "нет") << endl << endl;

    // ===== 5) РАДИУС ВПИСАННОЙ ОКРУЖНОСТИ =====
    cout << "5) Радиус вписанной окружности t2 = " << t2.inRadius() << endl << endl;

    // ===== 6) ЦЕНТР ВПИСАННОЙ ОКРУЖНОСТИ =====
    double cx, cy;
    t2.inCenter(cx, cy);
    cout << "6) Центр вписанной окружности t2: (" << cx << ", " << cy << ")" << endl << endl;

    // ===== 7) БОЛЬШИЙ УГОЛ =====
    cout << "7) Больший угол t2 = " << t2.largerAngle() * 180.0 / M_PI << " градусов" << endl << endl;

    // ===== 8) МАСШТАБИРОВАНИЕ =====
    Triangle t4 = t2 * 2.0;
    cout << "8) t2 * 2 = " << t4 << endl << endl;

    // ===== 9) ПОДОБИЕ =====
    Triangle t5(10, 10, 8, 6);
    cout << "9) t2 подобен t5? " << (t2 == t5 ? "да" : "нет") << endl;

    Triangle t6(0, 0, 4, 5);
    cout << "9) t2 подобен t6? " << (t2 == t6 ? "да" : "нет") << endl << endl;

    // ===== 10) ДЛИНЫ БОКОВЫХ СТОРОН =====
    cout << "10) Боковая сторона t2 = " << t2.sideLength() << endl;

  
        
   

    return 0;
}













