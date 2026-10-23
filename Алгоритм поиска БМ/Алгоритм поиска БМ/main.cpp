#define NOMINMAX
#include <windows.h>
#include <iostream>
#include <string>
#include <limits>
#include "BoyerMoore.h"

static int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            return value;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');     
        std::cout << "ОШибка.'\n'";                                            
    }
}

static std::string readLine(const std::string& prompt) {
    std::string s;
    std::cout << prompt;
    std::getline(std::cin, s);
    return s;
}

    

    

int main() {
    SetConsoleCP(1251);

    std::cout << "===== Алгоритм Бойера-Мура =====\n\n";

    std::string text = readLine("Введите текст: ");
    std::string pattern = readLine("Введите искомую подстроку: ");

    if (pattern.empty()) {
        std::cout << "Подстрока пустая — поиск невозможен.\n";
        return 0;
    }

    BoyerMoore bm(pattern);

    // 1. Первое вхождение
    int first = bm.findFirst(text);
    if (first == -1)
        std::cout << "\n[1] Первое вхождение: не найдено\n";
    else
        std::cout << "\n[1] Первое вхождение: индекс " << first << '\n';

    // 2. Все вхождения
    auto all = bm.findAll(text);
    std::cout << "[2] Все вхождения (" << all.size() << " шт.): ";
    if (all.empty()) std::cout << "нет";
    else for (int p : all) std::cout << p << ' ';
    std::cout << '\n';

    // 3. Вхождения в диапазоне
    std::cout << "\n[3] Поиск в диапазоне\n";
    int from = readInt("    Начало диапазона (индекс): ");
    int to = readInt("    Конец диапазона (индекс): ");

    auto range = bm.findInRange(text, from, to);
    std::cout << "[3] Вхождения в [" << from << ".." << to << "]: ";
    if (range.empty()) std::cout << "нет";
    else for (int p : range) std::cout << p << ' ';
    std::cout << '\n';

    return 0;
}