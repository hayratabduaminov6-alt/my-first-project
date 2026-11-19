#pragma once
#include <iostream>

template <typename T> class DynamicArray;

template <typename T>
std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& arr);

template <typename T>
std::istream& operator>>(std::istream& is, DynamicArray<T>& arr);

template <typename T>
class DynamicArray
{
private:
    T* data;
    int size;
    int capacity;

public:
    // 1. Конструкторы
    DynamicArray();
    DynamicArray(const T* arr, int count);
    DynamicArray(const DynamicArray& other);

    // 2. Деструктор
    ~DynamicArray();

    // 3. Получение размера
    int getSize() const;

    // 4. Обмен содержимого
    void swap(DynamicArray& other);

    // 5. Поиск элемента
    int indexOf(T value) const;

    // 7. Сортировка
    void sort();

    // 8. Вставка по индексу
    bool insertAt(int index, T value);

    // 9. Удаление по индексу
    bool removeAt(int index);

    // 10. Удаление по значению
    bool removeByValue(T value);

    // 11. Удаление всех с заданным значением
    bool removeAllByValue(T value);

    // 12. Минимум и максимум
    T findMin() const;
    T findMax() const;

    // 14. Итераторы
    typedef T* iterator;
    typedef const T* const_iterator;
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    // 15. Вставка перед итератором
    iterator insert(iterator pos, T value);

    // 16. Удаление по итератору
    iterator erase(iterator pos);

    // Вспомогательный метод
    void add(T value);

    friend std::ostream& operator<< <T>(std::ostream& os, const DynamicArray<T>& arr);
    friend std::istream& operator>> <T>(std::istream& is, DynamicArray<T>& arr);
};

#include "tempel_array.inl"