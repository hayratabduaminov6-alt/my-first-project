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
    DynamicArray(DynamicArray&& other) noexcept; // Перемещение

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

    // 17. Удаление диапазона [first, last)
    iterator erase(iterator first, iterator last);

    // 19. Перегрузки операторов
    T& operator[](int index);
    const T& operator[](int index) const;
    DynamicArray& operator=(const DynamicArray& other);
    DynamicArray& operator+=(T value);
    DynamicArray operator+(T value) const;
    DynamicArray& operator+=(const DynamicArray& other);
    DynamicArray operator+(const DynamicArray& other) const;
    DynamicArray& operator=(DynamicArray&& other) noexcept;
    bool operator==(const DynamicArray& other) const;
    bool operator!=(const DynamicArray& other) const;

    // Вспомогательный метод
    void add(T value);

    friend std::ostream& operator<< <T>(std::ostream& os, const DynamicArray<T>& arr);
    friend std::istream& operator>> <T>(std::istream& is, DynamicArray<T>& arr);
};

#include "tempel_array.inl"