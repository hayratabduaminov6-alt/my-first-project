// 1. Конструкторы
template <typename T>
DynamicArray<T>::DynamicArray() { capacity = 2; size = 0; data = new T[capacity]; }

template <typename T>
DynamicArray<T>::DynamicArray(const T* arr, int count)
{
    if (count <= 0) { capacity = 2; size = 0; data = new T[capacity]; }
    else {
        capacity = count; size = count; data = new T[capacity];
        for (int i = 0; i < count; i++) data[i] = arr[i];
    }
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other)
{
    size = other.size; capacity = other.capacity; data = new T[capacity];
    for (int i = 0; i < size; i++) data[i] = other.data[i];
}

// 2. Деструктор
template <typename T>
DynamicArray<T>::~DynamicArray() { delete[] data; }

// 3. Размер
template <typename T>
int DynamicArray<T>::getSize() const { return size; }

// 4. Swap
template <typename T>
void DynamicArray<T>::swap(DynamicArray& other)
{
    T* tempData = data; data = other.data; other.data = tempData;
    int tempSize = size; size = other.size; other.size = tempSize;
    int tempCap = capacity; capacity = other.capacity; other.capacity = tempCap;
}

// 5. Поиск
template <typename T>
int DynamicArray<T>::indexOf(T value) const
{
    for (int i = 0; i < size; i++) if (data[i] == value) return i;
    return -1;
}

// 7. Сортировка
template <typename T>
void DynamicArray<T>::sort()
{
    for (int gap = size / 2; gap > 0; gap = gap / 2)
        for (int b = 0; b < gap; b++) {
            int j = b + gap;
            while (j < size) {
                T x = data[j]; int k = j - gap;
                while (k >= 0 && data[k] > x) { data[k + gap] = data[k]; k = k - gap; }
                data[k + gap] = x; j = j + gap;
            }
        }
}

// 8. Вставка
template <typename T>
bool DynamicArray<T>::insertAt(int index, T value)
{
    if (index < 0 || index > size) return false;
    if (size == capacity) {
        int newCapacity = capacity * 2;
        T* newData = new T[newCapacity];
        for (int i = 0; i < size; i++) newData[i] = data[i];
        delete[] data; data = newData; capacity = newCapacity;
    }
    for (int i = size - 1; i >= index; i--) data[i + 1] = data[i];
    data[index] = value; size++; return true;
}

// 9. Удаление по индексу
template <typename T>
bool DynamicArray<T>::removeAt(int index)
{
    if (index < 0 || index >= size) return false;
    for (int i = index; i < size - 1; i++) data[i] = data[i + 1];
    size--;
    if (capacity > 2 && size < capacity / 2) {
        int newCapacity = capacity / 2;
        T* newData = new T[newCapacity];
        for (int i = 0; i < size; i++) newData[i] = data[i];
        delete[] data; data = newData; capacity = newCapacity;
    }
    return true;
}

// 10. Удаление по значению
template <typename T>
bool DynamicArray<T>::removeByValue(T value)
{
    int index = indexOf(value);
    if (index == -1) return false;
    removeAt(index); return true;
}

// Вспомогательный
template <typename T>
void DynamicArray<T>::add(T value)
{
    if (size == capacity) {
        int newCapacity = capacity * 2;
        T* newData = new T[newCapacity];
        for (int i = 0; i < size; i++) newData[i] = data[i];
        delete[] data; data = newData; capacity = newCapacity;
    }
    data[size] = value; size++;
}

// Потоковый вывод
template <typename T>
std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& arr)
{
    os << "["; for (int i = 0; i < arr.size; i++) { os << arr.data[i]; if (i < arr.size - 1) os << ", "; }
    os << "]"; return os;
}

// Потоковый ввод
template <typename T>
std::istream& operator>>(std::istream& is, DynamicArray<T>& arr)
{
    int n; std::cout << "Сколько элементов ввести? "; is >> n;
    while (arr.size > 0) arr.removeAt(arr.size - 1);
    for (int i = 0; i < n; i++) { T value; std::cout << "Элемент " << (i + 1) << ": "; is >> value; arr.insertAt(arr.size, value); }
    return is;
}