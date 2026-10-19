#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H

#include <string>
#include <vector>

class BoyerMoore {
public:
    explicit BoyerMoore(const std::string& pattern);

    
    int findFirst(const std::string& text) const;

   
    std::vector<int> findAll(const std::string& text) const;
 // 3. Вхождения в диапазоне [from, to] текста
    std::vector<int> findInRange(const std::string& text, int from, int to) const;

private:
    std::string pattern_;
    int m_;
    int badChar_[256];

    void buildBadChar();
    int badCharShift(char c, int j) const;
};

#endif