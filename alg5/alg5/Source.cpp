#include <iostream>
#include <fstream>
#include <string>
#include <chrono> 
#include <iomanip> 

using namespace std;


bool isSorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

void loadArrayFromFile(int arr[], string filename) {
    ifstream file(filename);
    if (!file.is_open()) return;
    int size;
    file >> size;
    for (int i = 0; i < size; i++) {
        file >> arr[i];
    }
    file.close();
}


void hoareSort(int arr[], int l, int r) {
    
    if (l >= r) return;

    int i = l;
    int j = r;

  
    int x = arr[(l + r) / 2];

   
    while (i <= j) {
       
        while (arr[i] < x) {
            i++;
        }
        
        while (arr[j] > x) {
            j--;
        }

        if (i <= j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    
    if (l < j) {
        hoareSort(arr, l, j);
    }
    if (i < r) {
        hoareSort(arr, i, r);
    }
}


void quickSort(int arr[], int n) {
    hoareSort(arr, 0, n - 1);
}


double getAverageTime(int size, string filename) {
    int* workArr = new int[size];
    double totalTime = 0.0;

    for (int run = 1; run <= 3; run++) {
        
        loadArrayFromFile(workArr, filename);

        auto start = chrono::high_resolution_clock::now();

        
        quickSort(workArr, size);

        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> elapsed = end - start;
        totalTime += elapsed.count();
    }

   
    if (!isSorted(workArr, size)) {
        cout << "ОШИБКА СОРТИРОВКИ В ФАЙЛЕ " << filename << "!" << endl;
    }

    delete[] workArr;
    return totalTime / 3.0;
}

int main() {
   
    int sizes[] = { 10000, 100000, 1000000 };
    int mins[] = { -10, -1000, -100000 };
    int maxs[] = { 10, 1000, 100000 };

    cout << "Размер\t| Диапазон\t\t| Среднее время (мс)" << endl;
    cout << "-----------------------------------------------------------------" << endl;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int currentSize = sizes[i];
            int currentMin = mins[j];
            int currentMax = maxs[j];

            
            string filename = "array_" + to_string(currentSize) + "_" + to_string(currentMin) + "_" + to_string(currentMax) + ".txt";

           
            ifstream check(filename);
            if (!check) {
                cout << "ОШИБКА: Нет файла " << filename << endl;
                return 1;
            }
            check.close();

           
            double avgTime = getAverageTime(currentSize, filename);

            cout << currentSize << "\t| [" << currentMin << "; " << currentMax << "]\t\t| "
                << fixed << setprecision(4) << avgTime << endl;
        }
    }

    return 0;
}