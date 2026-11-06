#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <chrono>
using namespace std;


bool isSorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}


void shellSort(int arr[], int n, int steps[], int t) {
    for (int i = 0; i < t; i++) {
        int s = steps[i];
        for (int b = 0; b < s; b++) {
            int j = b + s;
            while (j < n) {
                int x = arr[j];
                int k = j - s;
                while (k >= 0 && arr[k] > x) {
                    arr[k + s] = arr[k];
                    k = k - s;
                }
                arr[k + s] = x;
                j = j + s;
            }
        }
    }
}


int getShellSteps(int n, int steps[]) {
    int count = 0;
    for (int h = n / 2; h > 0; h = h / 2) { steps[count++] = h; }
    return count;
}

int getKnuthSteps(int n, int steps[]) {
    int h = 1;
    while (h < n / 3) h = 3 * h + 1;
    int count = 0;
    while (h > 0) {
        steps[count++] = h;
        h = (h - 1) / 3;
    }
    return count;
}

int getHibbardSteps(int n, int steps[]) {
    int count = 0;
    int h = 1;
    while (h < n) {
        steps[count++] = h;
        h = h * 2 + 1;
    }
    for (int i = 0; i < count / 2; i++) {
        int temp = steps[i];
        steps[i] = steps[count - 1 - i];
        steps[count - 1 - i] = temp;
    }
    return count;
}


void saveArrayToFile(int arr[], int size, string filename) {
    ofstream file(filename);
    if (!file.is_open()) return;
    file << size << endl;
    for (int i = 0; i < size; i++) file << arr[i] << " ";
    file.close();
}

void loadArrayFromFile(int arr[], string filename) {
    ifstream file(filename);
    if (!file.is_open()) return;
    int size;
    file >> size;
    for (int i = 0; i < size; i++) file >> arr[i];
    file.close();
}


double getAverageTime(int size, string filename, int method) {
    int steps[50];
    int stepsCount = 0;
    int* workArr = new int[size];

    if (method == 1) stepsCount = getShellSteps(size, steps);
    else if (method == 2) stepsCount = getKnuthSteps(size, steps);
    else stepsCount = getHibbardSteps(size, steps);

    double totalTime = 0.0;
    for (int run = 1; run <= 3; run++) {
        loadArrayFromFile(workArr, filename);

        auto start = chrono::high_resolution_clock::now();
        shellSort(workArr, size, steps, stepsCount);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> elapsed = end - start;
        totalTime += elapsed.count();
    }

    if (!isSorted(workArr, size)) {
        cout << "ОШИБКА СОРТИРОВКИ!" << endl;
    }

    delete[] workArr;
    return totalTime / 3.0;
}


int main() {
    int sizes[] = { 10000, 100000, 1000000 };
    int mins[] = { -10, -1000, -100000 };
    int maxs[] = { 10, 1000, 100000 };

    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            string filename = "array_" + to_string(sizes[i]) + "_" + to_string(mins[j]) + "_" + to_string(maxs[j]) + ".txt";

            ifstream testFile(filename);
            if (!testFile.is_open()) {
              
                cout << "ОШИБКА: Файл " << filename << " не найден!" << endl;
                cout << "Убедитесь, что все 9 файлов лежат в папке с программой." << endl;
                return 1; 
            }
            testFile.close();
        }
    }
   

   

    cout << "Размер\t| Диапазон\t\t|  Шелл (мс)\t        |   Кнут (мс)\t        | Хиббард (мс)" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;


    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            int currentSize = sizes[i];
            int currentMin = mins[j];
            int currentMax = maxs[j];
            string filename = "array_" + to_string(currentSize) + "_" + to_string(currentMin) + "_" + to_string(currentMax) + ".txt";


            double tShell = getAverageTime(currentSize, filename, 1);
            double tKnuth = getAverageTime(currentSize, filename, 2);
            double tHibbard = getAverageTime(currentSize, filename, 3);


            cout << currentSize << "\t| [" << currentMin << "; " << currentMax << "]\t\t| "
                << tShell << "\t\t| "
                << tKnuth << "\t\t| "
                << tHibbard << endl;
        }
    }


    return 0;
}