
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>
#include <consoleapi2.h>

class BoyerMoore {
public:
    explicit BoyerMoore(const std::string& pattern)
        : pattern_(pattern), m_(static_cast<int>(pattern.size()))
    {
        buildBadChar();
        buildGoodSuffix();
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

            int badShift = badCharShift(text[shift + j], j);
            int goodShift = goodSuffixShift(j);
            shift += std::max(1, std::max(badShift, goodShift));
        }
        return -1;
    }

    // 2. Все вхождения
    std::vector<int> findAll(const std::string& text) const {
        return findInRange(text, 0, static_cast<int>(text.size()) - 1);
    }

    // 3. Вхождения в диапазоне [from, to]
    std::vector<int> findInRange(const std::string& text,
        int from, int to) const
    {
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
                shift += std::max(1, goodSuffixShift(0));
            }
            else {
                int badShift = badCharShift(text[shift + j], j);
                int goodShift = goodSuffixShift(j);
                shift += std::max(1, std::max(badShift, goodShift));
            }
        }
        return result;
    }

private:
    std::string pattern_;
    int m_;
    int badChar_[256];
    std::vector<int> goodSuffix_;

    void buildBadChar() {
        for (int i = 0; i < 256; ++i)
            badChar_[i] = m_;
        for (int i = 0; i < m_; ++i)
            badChar_[static_cast<unsigned char>(pattern_[i])] = m_ - 1 - i;
    }

    void buildGoodSuffix() {
        goodSuffix_.assign(m_, 1);
        if (m_ == 1) return;

        std::vector<int> suff(m_, 0);
        suff[m_ - 1] = m_;
        int g = m_ - 1, f = 0;
        for (int i = m_ - 2; i >= 0; --i) {
            if (i > g && suff[i + m_ - 1 - f] < i - g)
                suff[i] = suff[i + m_ - 1 - f];
            else {
                if (i < g) g = i;
                f = i;
                while (g >= 0 && pattern_[g] == pattern_[g + m_ - 1 - f])
                    --g;
                suff[i] = f - g;
            }
        }

        for (int i = 0; i < m_ - 1; ++i)
            goodSuffix_[i] = m_;
        int j = 0;
        for (int i = m_ - 1; i >= 0; --i) {
            if (suff[i] == i + 1) {
                for (; j < m_ - 1 - i; ++j)
                    goodSuffix_[j] = m_ - 1 - i;
            }
        }
        for (int i = 0; i <= m_ - 2; ++i)
            goodSuffix_[m_ - 1 - suff[i]] = m_ - 1 - i;
    }

    int badCharShift(char c, int j) const {
        int last = badChar_[static_cast<unsigned char>(c)];
        return j - (m_ - 1 - last);
    }

    int goodSuffixShift(int j) const {
        return goodSuffix_[j];
    }
};

// ---------- Вспомогательные функции ввода ----------
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

// ---------- main ----------
int main() {
   


    std::cout << "===== Алгоритм Бойера-Мура =====\n\n";

    std::string text = readLine("Введите текст: ");
    std::string pattern = readLine("Введите искомую подстроку: ");

    if (pattern.empty()) {
        std::cout << "Подстрока пустая — поиск невозможен.\n";
        return 0;
    }

    // Проверка: сколько байт занимает подстрока
    std::cout << "(длина подстроки в байтах: " << pattern.size() << ")\n";

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