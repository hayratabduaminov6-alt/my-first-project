#include "BoyerMoore.h"
#include <algorithm>

BoyerMoore::BoyerMoore(const std::string& pattern)
    : pattern_(pattern), m_(static_cast<int>(pattern.size()))
{
    buildBadChar();
    buildGoodSuffix();
}

int BoyerMoore::findFirst(const std::string& text) const {
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

std::vector<int> BoyerMoore::findAll(const std::string& text) const {
    return findInRange(text, 0, static_cast<int>(text.size()) - 1);
}

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

void BoyerMoore::buildBadChar() {
    for (int i = 0; i < 256; ++i)
        badChar_[i] = m_;
    for (int i = 0; i < m_; ++i)
        badChar_[static_cast<unsigned char>(pattern_[i])] = m_ - 1 - i;
}

void BoyerMoore::buildGoodSuffix() {
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

int BoyerMoore::badCharShift(char c, int j) const {
    int last = badChar_[static_cast<unsigned char>(c)];
    return j - (m_ - 1 - last);
}

int BoyerMoore::goodSuffixShift(int j) const {
    return goodSuffix_[j];
}