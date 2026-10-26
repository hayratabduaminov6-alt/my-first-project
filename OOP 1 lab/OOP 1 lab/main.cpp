#define _USE_MATH_DEFINES
#include "Triangle.h"
#include <iostream>
#include <cmath>
#include <Windows.h>
#include <locale.h>

using namespace std;

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


    // ===== 11) ВЫСОТА, ОПУЩЕННАЯ НА БОКОВУЮ СТОРОНУ =====
    cout << "11) Высота на боковую сторону t2 = " << t2.heightToSide() << endl << endl;

    // ===== 12) ПЕРЕСЕЧЕНИЕ С ПРЯМОЙ =====
    // t2: x=0, y=0, base=4, height=3
    //   T=(2,0), L=(0,3), R=(4,3)

    // Прямая y = 1
    cout << "12) Прямая y=1 пересекает t2? "
        << (t2.intersectsLine(0, 1, -1) ? "да" : "нет") << endl;

    // Прямая y = 5
    cout << "12) Прямая y=5 пересекает t2? "
        << (t2.intersectsLine(0, 1, -5) ? "да" : "нет") << endl;

    // Прямая y = -2
    cout << "12) Прямая y=-2 пересекает t2? "
        << (t2.intersectsLine(0, 1, 2) ? "да" : "нет") << endl;

    // Прямая x = 2
    cout << "12) Прямая x=2 пересекает t2? "
        << (t2.intersectsLine(1, 0, -2) ? "да" : "нет") << endl;

    // Прямая x = -1
    cout << "12) Прямая x=-1 пересекает t2? "
        << (t2.intersectsLine(1, 0, 1) ? "да" : "нет") << endl;

    // Прямая x + y - 3 = 0 (проходит через L=(0,3))
    cout << "12) Прямая x+y-3=0 пересекает t2? "
        << (t2.intersectsLine(1, 1, -3) ? "да" : "нет") << endl;

    return 0;
}





