#include "BoyerMoore.h"
#include <algorithm>

BoyerMoore::BoyerMoore(const std::string& pattern)
    : pattern_(pattern), m_(static_cast<int>(pattern.size()))
{
    buildBadChar();
}

// ---------- 1. Первое вхождение ----------
int BoyerMoore::findFirst(const std::string& text) const {
    int n = static_cast<int>(text.size());
    if (m_ == 0) return 0;
    if (m_ > n)  return -1;

    int shift = 0;                       // аналог i в псевдокоде
    while (shift <= n - m_) {
        int j = m_ - 1;                  // j = m - 1
        while (j >= 0 && pattern_[j] == text[shift + j])
            --j;

        if (j < 0)
            return shift;                // нашли

        // i = i + T[S[i]]
        shift += std::max(1, badCharShift(text[shift + j], j));
    }
    return -1;
}

// ---------- 2. Все вхождения ----------
std::vector<int> BoyerMoore::findAll(const std::string& text) const {
    return findInRange(text, 0, static_cast<int>(text.size()) - 1);
}

// ---------- 3. Вхождения в диапазоне ----------
std::vector<int> BoyerMoore::findInRange(const std::string& text, int from, int to) const {
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

            // Сдвиг после найденного вхождения:
            // используем плохой символ для последнего символа окна
            shift += std::max(1, badCharShift(text[shift + m_ - 1], m_ - 1));
        }
        else {
            shift += std::max(1, badCharShift(text[shift + j], j));
        }
    }
    return result;
}

// ---------- Таблица плохих символов ----------
void BoyerMoore::buildBadChar() {
    for (int i = 0; i < 256; ++i)
        badChar_[i] = m_;
    for (int i = 0; i < m_; ++i)
        badChar_[static_cast<unsigned char>(pattern_[i])] = m_ - 1 - i;
}

int BoyerMoore::badCharShift(char c, int j) const {
    int last = badChar_[static_cast<unsigned char>(c)];
    return j - (m_ - 1 - last);
}