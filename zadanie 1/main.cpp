#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <climits>

using namespace std;

// Функция для заполнения матрицы случайными значениями
vector<vector<int>> generateMatrix(int n, int minCost, int maxCost, mt19937_64& gen) {
    uniform_int_distribution<int> dist(minCost, maxCost);
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                matrix[i][j] = 0; // Путь в самого себя равен 0
            }
            else {
                matrix[i][j] = dist(gen);
            }
        }
    }
    return matrix;
}

// Структура для сохранения результатов
struct ExactResult {
    int minCost = INT_MAX;
    int maxCost = INT_MIN;
};

// Точное решение задачи коммивояжера (Полный перебор)
ExactResult solveExact(const vector<vector<int>>& matrix, int startCity) {
    int n = matrix.size();
    vector<int> cities;
    for (int i = 0; i < n; ++i) {
        if (i != startCity) cities.push_back(i);
    }

    ExactResult res;

    // Перебор всех перестановок
    do {
        int currentCost = 0;
        int currentCity = startCity;

        for (int nextCity : cities) {
            currentCost += matrix[currentCity][nextCity];
            currentCity = nextCity;
        }
        currentCost += matrix[currentCity][startCity];

        res.minCost = min(res.minCost, currentCost);
        res.maxCost = max(res.maxCost, currentCost);

    } while (next_permutation(cities.begin(), cities.end()));

    return res;
}

int main() {
    random_device rd;
    mt19937_64 gen(rd());

    int n = 4;
    auto matrix = generateMatrix(n, 10, 100, gen);
    ExactResult res = solveExact(matrix, 0);

    cout << "Точное наилучшее: " << res.minCost << endl;
    cout << "Точное наихудшее: " << res.maxCost << endl;

    return 0;
}