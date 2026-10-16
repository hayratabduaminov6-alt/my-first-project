#define NOMINMAX
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

// ============================================================
//                    КЛАСС BoyerMoore
// ============================================================
class BoyerMoore {
public:
    explicit BoyerMoore(const std::string& pattern)
        : pattern_(pattern), m_(static_cast<int>(pattern.size()))
    {
        buildBadChar();
    }

    // 1. Индекс первого вхождения или -1
    int findFirst(const std::string& text) const {
        int n = static_cast<int>(text.size());
        if (m_ == 0) return 0;
        if (m_ > n)  return -1;

        int shift = 0;
        while (shift <= n - m_) {
            int j = m_ - 1;
            while (j >= 0 && pattern_[j] == text[shift + j])
                --j;

            if (j < 0)
                return shift;

            // i = i + T[S[i]]
            shift += std::max(1, badCharShift(text[shift + j], j));
        }
        return -1;
    }

    // 2. Все вхождения
    std::vector<int> findAll(const std::string& text) const {
        return findInRange(text, 0, static_cast<int>(text.size()) - 1);
    }

    // 3. Вхождения в диапазоне [from, to]
    std::vector<int> findInRange(const std::string& text, int from, int to) const {
        std::vector<int> result;
        int n = static_cast<int>(text.size());

        if (m_ == 0) {
            for (int i = std::max(0, from); i <= std::min(to, n); ++i)
                result.push_back(i);
            return result;
        }

        if (from < 0) from = 0;
        if (to >= n)  to = n - 1;
        if (from > to || m_ > to - from + 1) return result;

        int limit = to - m_ + 1;
        int shift = from;

        while (shift <= limit) {
            int j = m_ - 1;
            while (j >= 0 && pattern_[j] == text[shift + j])
                --j;

            if (j < 0) {
                result.push_back(shift);
                // сдвиг после найденного вхождения — по последнему символу окна
                shift += std::max(1, badCharShift(text[shift + m_ - 1], m_ - 1));
            }
            else {
                shift += std::max(1, badCharShift(text[shift + j], j));
            }
        }
        return result;
    }

private:
    std::string pattern_;
    int m_;
    int badChar_[256];

    void buildBadChar() {
        for (int i = 0; i < 256; ++i)
            badChar_[i] = m_;
        for (int i = 0; i < m_; ++i)
            badChar_[static_cast<unsigned char>(pattern_[i])] = m_ - 1 - i;
    }

    int badCharShift(char c, int j) const {
        int last = badChar_[static_cast<unsigned char>(c)];
        return j - (m_ - 1 - last);
    }
};

// ============================================================
//                 ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ВВОДА
// ============================================================
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
        std::cout << "Ошибка: введите целое число.\n";
    }
}

static std::string readLine(const std::string& prompt) {
    std::string s;
    std::cout << prompt;
    std::getline(std::cin, s);
    return s;
}

// ============================================================
//                         MAIN
// ============================================================
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