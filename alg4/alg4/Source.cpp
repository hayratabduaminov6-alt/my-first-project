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



void siftDown(int arr[], int n, int i) {
    int j = 2 * i + 1;
    int x = arr[i];
    bool f = 1;

    while (j < n && f) {
      
        if (j + 1 < n && arr[j + 1] > arr[j]) {
            j = j + 1;
        }

        
        if (arr[j] > x) {
            arr[i] = arr[j];
            i = j;
            j = 2 * i + 1;
        }
        else {
            f = 0;
        }
    }
    arr[i] = x; 
}


void heapSort(int arr[], int n) {
    
    for (int i = n / 2 - 1; i >= 0; i--) {
        siftDown(arr, n, i);
    }

   
    for (int i = n - 1; i > 0; i--) {
        
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
       
        
      
        siftDown(arr, i, 0);
    }
}


double getAverageTime(int size, string filename) {
    int* workArr = new int[size];
    double totalTime = 0.0;

    
    for (int run = 1; run <= 3; run++) {
   
        loadArrayFromFile(workArr, filename);

       
        auto start = chrono::high_resolution_clock::now();

      
        heapSort(workArr, size);

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