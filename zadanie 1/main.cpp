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


// Алгоритм Дейкстры 
bool next_permutation_silent(int* p, int n) {
    int i = n - 2;
    while (i >= 0 && p[i] >= p[i + 1]) {
        i--;
    }
    if (i < 0) return false;

    int j = n - 1;
    while (p[i] >= p[j]) {
        j--;
    }

    std::swap(p[i], p[j]);

    int left = i + 1;
    int right = n - 1;
    while (left < right) {
        std::swap(p[left], p[right]);
        left++;
        right--;
    }

    return true;
}

// Алгоритм   Алгоритм Дейкстры — решение после замены и инвертирования хвоста
bool next_permutation_verbose(int* p, int n) {
    int i = n - 2;
    while (i >= 0 && p[i] >= p[i + 1]) {
        i--;
    }
    if (i < 0) return false;

    int j = n - 1;
    while (p[i] >= p[j]) {
        j--;
    }


    cout << "1. i = " << i + 1 << endl;


    cout << "2. j = " << j + 1 << endl;


    std::swap(p[i], p[j]);
    cout << "3. P = (";
    for (int k = 0; k < n; ++k) {
        cout << p[k];
        if (k < n - 1) cout << ", ";
    }
    cout << ")" << endl;


    int left = i + 1;
    int right = n - 1;
    while (left < right) {
        std::swap(p[left], p[right]);
        left++;
        right--;
    }
    cout << "4. P = (";
    for (int k = 0; k < n; ++k) {
        cout << p[k];
        if (k < n - 1) cout << ", ";
    }
    cout << ")" << endl;

    return true;
}

// Результаты точного метода

struct ExactResult {
    int minCost = INT_MAX;
    int maxCost = INT_MIN;
    double timeMs = 0.0;
};

ExactResult solveExact(const vector<vector<int>>& matrix, int startCity) {
    int n = matrix.size();
    vector<int> citiesVec;
    for (int i = 0; i < n; ++i) {
        if (i != startCity) citiesVec.push_back(i);
    }

    sort(citiesVec.begin(), citiesVec.end());

    int m = citiesVec.size();
    int* cities = new int[m];
    for (int i = 0; i < m; ++i) {
        cities[i] = citiesVec[i];
    }

    auto t1 = chrono::high_resolution_clock::now();
    ExactResult res;

    do {
        int currentCost = 0;
        int currentCity = startCity;

        for (int i = 0; i < m; ++i) {
            int nextCity = cities[i];
            currentCost += matrix[currentCity][nextCity];
            currentCity = nextCity;
        }
        currentCost += matrix[currentCity][startCity];

        res.minCost = min(res.minCost, currentCost);
        res.maxCost = max(res.maxCost, currentCost);

    } while (next_permutation_silent(cities, m));

    auto t2 = chrono::high_resolution_clock::now();
    res.timeMs = chrono::duration<double, milli>(t2 - t1).count();

    delete[] cities;
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


// массив после замены и после инвертирования хвоста 
void demonstrateNextPermutation() {
    cout << "\nАлгоритм Дейкстры" << endl;


    int p[] = { 6, 5, 4, 2, 3, 1 };
    int n = sizeof(p) / sizeof(p[0]);

    cout << "Исходная перестановка: P = (";
    for (int k = 0; k < n; ++k) {
        cout << p[k];
        if (k < n - 1) cout << ", ";
    }
    cout << ")\n" << endl;

    // Однократное применение next_permutation с выводом шагов
    if (next_permutation_verbose(p, n)) {
        cout << "\nСледующая перестановка: P = (";
        for (int k = 0; k < n; ++k) {
            cout << p[k];
            if (k < n - 1) cout << ", ";
        }
        cout << ")" << endl;
    }
    else {
        cout << "Это была последняя перестановка." << endl;
    }

    cout << "=====================================================================" << endl;
}



int main() {
    random_device rd;
    mt19937_64 gen(rd());

    vector<int> sizes = { 4, 6, 8, 10 };
    int runsPerSize = 3;
    int minCost = 10, maxCost = 100;
    int startCity = 0;

    cout << fixed << setprecision(3);
    cout << "=================== ЭКСПЕРИМЕНТЫ TSP ===================" << endl;

    for (int n : sizes) {
        cout << "\n--------------------------------------------------" << endl;
        cout << "Размерность матрицы: " << n << "x" << n
            << " (Разброс стоимостей: " << minCost << "-" << maxCost << ")" << endl;
        cout << "--------------------------------------------------" << endl;

        for (int run = 1; run <= runsPerSize; ++run) {
            auto matrix = generateMatrix(n, minCost, maxCost, gen);

            ExactResult exact = solveExact(matrix, startCity);
            HeuristicResult heur = solveNearestNeighbor(matrix, startCity);

            double quality = 0.0;
            if (exact.maxCost != exact.minCost) {
                quality = 100.0 * (exact.maxCost - heur.cost) / (exact.maxCost - exact.minCost);
            }
            else {
                quality = 100.0;
            }

            cout << "Запуск #" << run << ":" << endl;
            cout << "  [Точный   ]  Мин: " << exact.minCost << " | Макс: " << exact.maxCost
                << " | Время: " << exact.timeMs << " ms" << endl;
            cout << "  [Эвристика]  Стоимость: " << heur.cost
                << " | Время: " << heur.timeMs << " ms" << endl;
            cout << "  [Качество ]: " << quality << "%" << endl;
        }
    }


    demonstrateNextPermutation();

    return 0;
}