#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <chrono>
#include <climits>
#include <iomanip>

using namespace std;

// Функция для заполнения матрицы случайными значениями
vector<vector<int>> generateMatrix(int n, int minCost, int maxCost, mt19937_64& gen) {
    uniform_int_distribution<int> dist(minCost, maxCost);
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) matrix[i][j] = 0;
            else matrix[i][j] = dist(gen);
        }
    }
    return matrix;
}

// Результаты точного метода
struct ExactResult {
    int minCost = INT_MAX;
    int maxCost = INT_MIN;
    double timeMs = 0.0;
};

ExactResult solveExact(const vector<vector<int>>& matrix, int startCity) {
    int n = matrix.size();
    vector<int> cities;
    for (int i = 0; i < n; ++i) {
        if (i != startCity) cities.push_back(i);
    }

    auto t1 = chrono::high_resolution_clock::now();
    ExactResult res;

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

    auto t2 = chrono::high_resolution_clock::now();
    res.timeMs = chrono::duration<double, milli>(t2 - t1).count();

    return res;
}

// Результаты эвристики
struct HeuristicResult {
    int cost = 0;
    double timeMs = 0.0;
};

HeuristicResult solveNearestNeighbor(const vector<vector<int>>& matrix, int startCity) {
    int n = matrix.size();
    vector<bool> visited(n, false);

    auto t1 = chrono::high_resolution_clock::now();

    int current = startCity;
    visited[current] = true;
    int totalCost = 0;

    for (int step = 0; step < n - 1; ++step) {
        int nearest = -1;
        int minEdge = INT_MAX;

        for (int next = 0; next < n; ++next) {
            if (!visited[next] && matrix[current][next] < minEdge) {
                minEdge = matrix[current][next];
                nearest = next;
            }
        }

        visited[nearest] = true;
        totalCost += minEdge;
        current = nearest;
    }

    totalCost += matrix[current][startCity];

    auto t2 = chrono::high_resolution_clock::now();

    HeuristicResult res;
    res.cost = totalCost;
    res.timeMs = chrono::duration<double, milli>(t2 - t1).count();

    return res;
}

int main() {
    random_device rd;
    mt19937_64 gen(rd());

    vector<int> sizes = { 4, 6, 8, 10 }; // Разные размерности
    int runsPerSize = 3;               // По 3 запуска на каждую размерность
    int minCost = 10, maxCost = 100;
    int startCity = 0;

    cout << fixed << setprecision(3);
    cout << "=================== ЭКСПЕРИМЕНТЫ TSP ===================" << endl;

    for (int n : sizes) {
        cout << "\n--------------------------------------------------" << endl;
        cout << "Размерность матрицы: " << n << "x" << n << " (Разброс стоимостей: " << minCost << "-" << maxCost << ")" << endl;
        cout << "--------------------------------------------------" << endl;

        for (int run = 1; run <= runsPerSize; ++run) {
            auto matrix = generateMatrix(n, minCost, maxCost, gen);

            ExactResult exact = solveExact(matrix, startCity);
            HeuristicResult heur = solveNearestNeighbor(matrix, startCity);

            // Формула качества: 100% - лучшее решение, 0% - худшее
            double quality = 0.0;
            if (exact.maxCost != exact.minCost) {
                quality = 100.0 * (exact.maxCost - heur.cost) / (exact.maxCost - exact.minCost);
            }
            else {
                quality = 100.0;
            }

            cout << "Запуск #" << run << ":" << endl;
            cout << "  [Точный]     Мин: " << exact.minCost << " | Макс: " << exact.maxCost
                << " | Время: " << exact.timeMs << " ms" << endl;
            cout << "  [Эвристика]  Стоимость: " << heur.cost
                << " | Время: " << heur.timeMs << " ms" << endl;
            cout << "  [Качество]:  " << quality << "%" << endl;
        }
    }

    return 0;
}