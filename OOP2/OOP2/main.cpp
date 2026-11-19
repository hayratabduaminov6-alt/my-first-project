#include <iostream>
#include <utility>
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
    search.insertAt(search.getSize(), 10);
    search.insertAt(search.getSize(), 20);
    search.insertAt(search.getSize(), 30);
    search.insertAt(search.getSize(), 20);
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

    cout << "\n=== 11. Удаление всех с заданным значением ===" << endl;
    int rawAll[7] = { 10, 20, 30, 20, 50, 20, 60 };
    DynamicArray<int> all(rawAll, 7);
    cout << "Исходный массив: " << all << endl;
    cout << "Удаление всех вхождений 20: " << all.removeAllByValue(20) << " -> " << all << endl;

    cout << "\n=== 12. Поиск минимума и максимума ===" << endl;
    DynamicArray<int> mm;
    mm.insertAt(mm.getSize(), 42); mm.insertAt(mm.getSize(), 7);
    mm.insertAt(mm.getSize(), 99); mm.insertAt(mm.getSize(), 13);
    mm.insertAt(mm.getSize(), 56);
    cout << "Массив: " << mm << endl;
    cout << "Минимальный элемент = " << mm.findMin() << endl;
    cout << "Максимальный элемент = " << mm.findMax() << endl;

    cout << "\n=== 14. Итераторы begin / end ===" << endl;
    DynamicArray<int> itArr;
    itArr.insertAt(itArr.getSize(), 10); itArr.insertAt(itArr.getSize(), 20);
    itArr.insertAt(itArr.getSize(), 30); itArr.insertAt(itArr.getSize(), 40);
    itArr.insertAt(itArr.getSize(), 50);
    cout << "Массив: " << itArr << endl;
    cout << "Проход через итераторы: ";
    for (DynamicArray<int>::iterator it = itArr.begin(); it != itArr.end(); ++it)
        cout << *it << " ";
    cout << endl;

    cout << "\n=== 15. Вставка перед итератором ===" << endl;
    DynamicArray<int> insIt;
    insIt.insertAt(0, 10); insIt.insertAt(1, 20); insIt.insertAt(2, 30);
    cout << "Исходный массив: " << insIt << endl;
    insIt.insert(insIt.begin() + 1, 15);
    cout << "Вставка 15 перед вторым элементом: " << insIt << endl;
    insIt.insert(insIt.begin(), 5);
    cout << "Вставка 5 в начало:                " << insIt << endl;
    insIt.insert(insIt.end(), 99);
    cout << "Вставка 99 в конец:                " << insIt << endl;

    cout << "\n=== 16. Удаление по итератору ===" << endl;
    DynamicArray<int> er;
    er.insertAt(0, 10); er.insertAt(1, 20); er.insertAt(2, 30);
    er.insertAt(3, 40); er.insertAt(4, 50);
    cout << "Исходный массив: " << er << endl;
    er.erase(er.begin());
    cout << "Удаление первого элемента:      " << er << endl;
    er.erase(er.begin() + 1);
    cout << "Удаление второго элемента:      " << er << endl;

    cout << "\n=== 17. Удаление диапазона [first, last) ===" << endl;
    DynamicArray<int> erRange;
    for (int i = 1; i <= 7; i++) erRange.insertAt(erRange.getSize(), i);
    cout << "Исходный массив: " << erRange << endl;
    erRange.erase(erRange.begin() + 2, erRange.begin() + 5);
    cout << "Удаление диапазона [2, 5): " << erRange << endl;

    cout << "\n=== 18. Конструктор перемещения ===" << endl;
    DynamicArray<int> src;
    src.insertAt(0, 100); src.insertAt(1, 200); src.insertAt(2, 300); src.insertAt(3, 400);
    cout << "Исходный массив до перемещения: " << src << endl;
    DynamicArray<int> dst = std::move(src);
    cout << "Новый массив после перемещения:  " << dst << endl;
    cout << "Исходный массив после перемещения: " << src << " (размер = " << src.getSize() << ")" << endl;

    cout << "\n=== 19. Оператор [] — доступ по индексу ===" << endl;
    DynamicArray<int> idxArr;
    idxArr.insertAt(0, 10); idxArr.insertAt(1, 20); idxArr.insertAt(2, 30);
    cout << "Исходный массив: " << idxArr << endl;
    cout << "Элемент с индексом 0 = " << idxArr[0] << endl;
    cout << "Элемент с индексом 2 = " << idxArr[2] << endl;
    idxArr[1] = 99;
    cout << "После записи idxArr[1] = 99: " << idxArr << endl;

    cout << "\n=== 20. Присваивание копированием ===" << endl;
    DynamicArray<int> src1;
    src1.insertAt(0, 1); src1.insertAt(1, 2); src1.insertAt(2, 3);
    DynamicArray<int> dst1;
    cout << "До:  исходный = " << src1 << ", копия = " << dst1 << endl;
    dst1 = src1;
    cout << "После присваивания:" << endl;
    cout << "  исходный = " << src1 << endl;
    cout << "  копия =    " << dst1 << endl;
    dst1[0] = 100;
    cout << "После изменения копии:" << endl;
    cout << "  исходный = " << src1 << " (не изменился)" << endl;
    cout << "  копия =    " << dst1 << endl;

    cout << "\n=== 21-22. Добавление элемента в конец (+ и +=) ===" << endl;
    DynamicArray<int> elemArr;
    elemArr.insertAt(0, 10); elemArr.insertAt(1, 20);
    cout << "Исходный массив: " << elemArr << endl;
    elemArr += 30;
    cout << "После += 30: " << elemArr << endl;
    DynamicArray<int> newElemArr = elemArr + 40;
    cout << "Результат elemArr + 40 = " << newElemArr << endl;
    cout << "Исходный массив не изменился: " << elemArr << endl;

    cout << "\n=== 23-24. Сложение с другим массивом (+ и +=) ===" << endl;
    DynamicArray<int> cat1; cat1.insertAt(0, 1); cat1.insertAt(1, 2);
    DynamicArray<int> cat2; cat2.insertAt(0, 3); cat2.insertAt(1, 4); cat2.insertAt(2, 5);
    cout << "Первый = " << cat1 << ", второй = " << cat2 << endl;
    DynamicArray<int> catSum = cat1 + cat2;
    cout << "Результат cat1 + cat2 = " << catSum << endl;
    cat1 += cat2;
    cout << "После cat1 += cat2: cat1 = " << cat1 << ", cat2 = " << cat2 << endl;

    cout << "\n=== 25. Присваивание перемещением ===" << endl;
    DynamicArray<int> moveSrc;
    moveSrc.insertAt(0, 100); moveSrc.insertAt(1, 200); moveSrc.insertAt(2, 300);
    DynamicArray<int> moveDst; moveDst.insertAt(0, 1);
    cout << "До:  исходный = " << moveSrc << ", приёмник = " << moveDst << endl;
    moveDst = std::move(moveSrc);
    cout << "После moveDst = std::move(moveSrc):" << endl;
    cout << "  приёмник = " << moveDst << endl;
    cout << "  исходный = " << moveSrc << " (размер = " << moveSrc.getSize() << ")" << endl;

    cout << "\n=== 26-27. Сравнение (== и !=) ===" << endl;
    DynamicArray<int> eq1, eq2, eq3;
    eq1.insertAt(0, 1); eq1.insertAt(1, 2); eq1.insertAt(2, 3);
    eq2.insertAt(0, 1); eq2.insertAt(1, 2); eq2.insertAt(2, 3);
    eq3.insertAt(0, 1); eq3.insertAt(1, 2); eq3.insertAt(2, 99);
    cout << "Первый =  " << eq1 << endl;
    cout << "Второй =  " << eq2 << endl;
    cout << "Третий =  " << eq3 << endl;
    cout << "Первый == второй?   " << (eq1 == eq2 ? "да" : "нет") << endl;
    cout << "Первый == третий?   " << (eq1 == eq3 ? "да" : "нет") << endl;
    cout << "Первый != третий?   " << (eq1 != eq3 ? "да" : "нет") << endl;

    cout << "\n=== 6. Потоковый ввод ===" << endl;
    DynamicArray<int> inputArr;
    cin >> inputArr;
    cout << "Вы ввели массив: " << inputArr << endl;

    return 0;
}