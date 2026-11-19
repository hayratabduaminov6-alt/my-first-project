#include <iostream>
#include "Temple_array.h"
using namespace std;

int main()
{
    cout << "=== 1. Конструкторы ===" << endl;
    DynamicArray<int> def;
    cout << "Пустой массив (по умолчанию): " << def << endl;
    int raw[5] = { 30, 10, 20, 40, 50 };
    DynamicArray<int> fromArr(raw, 5);
    cout << "Массив из обычного массива:   " << fromArr << endl;
    DynamicArray<int> copy(fromArr);
    cout << "Копия массива:                " << copy << endl;

    cout << "\n=== 2. Деструктор (вызывается автоматически) ===" << endl;

    cout << "\n=== 3. Получение размера ===" << endl;
    cout << "Размер массива = " << fromArr.getSize() << endl;

    cout << "\n=== 4. Обмен содержимого ===" << endl;
    DynamicArray<int> other;
    other.insertAt(other.getSize(), 100);
    other.insertAt(other.getSize(), 200);
    other.insertAt(other.getSize(), 300);
    cout << "До обмена:    первый = " << fromArr << ", второй = " << other << endl;
    fromArr.swap(other);
    cout << "После обмена: первый = " << fromArr << ", второй = " << other << endl;

    cout << "\n=== 5. Поиск элемента ===" << endl;
    DynamicArray<int> search;
    search.insertAt(search.getSize(), 10); search.insertAt(search.getSize(), 20);
    search.insertAt(search.getSize(), 30); search.insertAt(search.getSize(), 20);
    search.insertAt(search.getSize(), 50);
    cout << "Массив: " << search << endl;
    cout << "Индекс элемента 20 = " << search.indexOf(20) << endl;
    cout << "Индекс элемента 99 = " << search.indexOf(99) << " (нет такого)" << endl;

    cout << "\n=== 6. Потоковый вывод ===" << endl;
    cout << "Массив = " << search << endl;

    cout << "\n=== 7. Сортировка (Шелл) ===" << endl;
    DynamicArray<int> toSort;
    toSort.insertAt(toSort.getSize(), 5); toSort.insertAt(toSort.getSize(), 2);
    toSort.insertAt(toSort.getSize(), 9); toSort.insertAt(toSort.getSize(), 1);
    toSort.insertAt(toSort.getSize(), 5); toSort.insertAt(toSort.getSize(), 6);
    toSort.insertAt(toSort.getSize(), 3); toSort.insertAt(toSort.getSize(), 8);
    cout << "До сортировки:    " << toSort << endl;
    toSort.sort();
    cout << "После сортировки: " << toSort << endl;

    cout << "\n=== 8. Вставка по индексу ===" << endl;
    DynamicArray<int> ins;
    ins.insertAt(0, 10); ins.insertAt(1, 20); ins.insertAt(2, 30);
    cout << "Исходный массив: " << ins << endl;
    cout << "Вставка 5 в начало:     " << ins.insertAt(0, 5) << " -> " << ins << endl;
    cout << "Вставка 15 в индекс 2:  " << ins.insertAt(2, 15) << " -> " << ins << endl;
    cout << "Вставка 99 в конец:     " << ins.insertAt(ins.getSize(), 99) << " -> " << ins << endl;
    cout << "Вставка в индекс -1:    " << ins.insertAt(-1, 0) << " (некорректный)" << endl;

    cout << "\n=== 9. Удаление по индексу ===" << endl;
    int raw2[5] = { 10, 20, 30, 40, 50 };
    DynamicArray<int> a(raw2, 5);
    cout << "Исходный массив: " << a << endl;
    cout << "Удаление первого элемента:   " << a.removeAt(0) << " -> " << a << endl;
    cout << "Удаление третьего элемента:  " << a.removeAt(2) << " -> " << a << endl;
    cout << "Удаление последнего:         " << a.removeAt(a.getSize() - 1) << " -> " << a << endl;
    cout << "Удаление по индексу -1:      " << a.removeAt(-1) << " (некорректный)" << endl;

    cout << "\n=== 10. Удаление по значению ===" << endl;
    int raw3[5] = { 10, 20, 30, 20, 50 };
    DynamicArray<int> b(raw3, 5);
    cout << "Исходный массив: " << b << endl;
    cout << "Удаление первого вхождения 20: " << b.removeByValue(20) << " -> " << b << endl;
    cout << "Удаление 999 (нет такого):     " << b.removeByValue(999) << " -> " << b << endl;

    cout << "\n=== 6. Потоковый ввод ===" << endl;
    DynamicArray<int> inputArr;
    cin >> inputArr;
    cout << "Вы ввели массив: " << inputArr << endl;

    return 0;
}