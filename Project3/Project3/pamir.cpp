#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <iomanip>

using namespace std;

// Ïðîâåðêà îòñîðòèðîâàííîãî  ìàññèâà
bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

//ôóíêöèÿ äëÿ ðó÷íîãî ïåðåâîðîòà ìàññèâà øàãîâ
void reverseGaps(vector<int>& gaps) {
    int start = 0;
    int end = gaps.size() - 1;
    while (start < end) {
        int temp = gaps[start];
        gaps[start] = gaps[end];
        gaps[end] = temp;
        start++;
        end--;
    }
}

void shellSortOriginal(vector<int>& arr) {
    int n = arr.size();
    vector<int> gaps;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        gaps.push_back(gap);
    }
    int t = gaps.size() - 1;

    for (int i = 0; i <= t; ++i) {
        int s = gaps[i];
        for (int b = 0; b < s; ++b) {
            for (int j = b + s; j < n; j += s) {
                int x = arr[j];
                int k = j - s;
                while (k >= 0 && arr[k] > x) {
                    arr[k + s] = arr[k];
                    k = k - s;
                }
                arr[k + s] = x;
            }
        }
    }
}
void shellSortHibbard(vector<int>& arr) {
    int n = arr.size();
    vector<int> gaps;
    int m = 1;
    while (true) {
        int gap = (1 << m) - 1; // Áûñòðîå âîçâåäåíèå â ñòåïåíü 2^m - 1
        if (gap >= n) break;
        gaps.push_back(gap);
        m++;
    }
    reverseGaps(gaps); // Ðó÷íîé ïåðåâîðîò ìàññèâà øàãîâ
    int t = gaps.size() - 1;

    for (int i = 0; i <= t; ++i) {
        int s = gaps[i];
        for (int b = 0; b < s; ++b) {
            for (int j = b + s; j < n; j += s) {
                int x = arr[j];
                int k = j - s;
                while (k >= 0 && arr[k] > x) {
                    arr[k + s] = arr[k];
                    k = k - s;
                }
                arr[k + s] = x;
            }
        }
    }
}

void shellSortKnuth(vector<int>& arr) {
    int n = arr.size();
    vector<int> gaps;
    int gap = 1;
    while (gap < n) {
        gaps.push_back(gap);
        gap = 3 * gap + 1;
    }

    reverseGaps(gaps);
    int t = gaps.size() - 1;
    for (int i = 0; i <= t; ++i) {
        int s = gaps[i];
        for (int b = 0; b < s; ++b) {
            for (int j = b + s; j < n; j += s) {
                int x = arr[j];
                int k = j - s;
                while (k >= 0 && arr[k] > x) {
                    arr[k + s] = arr[k];
                    k = k - s;
                }
                arr[k + s] = x;
            }
        }
    }
}
void shellSortSedgewick(vector<int>& arr) {
    int n = arr.size();
    vector<int> gaps;
    int i = 0;
    while (true) {
        int gap;
        if (i % 2 == 0) {
            gap = 9 * (1 << i) - 9 * (1 << (i / 2)) + 1;
        }
        else {
            gap = 8 * (1 << i) - 6 * (1 << ((i + 1) / 2)) + 1;
        }

        if (gap >= n) break;
        gaps.push_back(gap);
        i++;
    }

    reverseGaps(gaps);
    int t = gaps.size() - 1;
    for (int idx = 0; idx <= t; ++idx) {
        int s = gaps[idx];
        for (int b = 0; b < s; ++b) {
            for (int j = b + s; j < n; j += s) {
                int x = arr[j];
                int k = j - s;
                while (k >= 0 && arr[k] > x) {
                    arr[k + s] = arr[k];
                    k = k - s;
                }
                arr[k + s] = x;
            }
        }
    }
}
// Ãåíåðàöèÿ ñëó÷àéíûõ ÷èñåë
void generateAndSaveArray(int size, int minVal, int maxVal, const char* filename) {
    mt19937 gen(1337);
    uniform_int_distribution<int> dis(minVal, maxVal);
    ofstream fout(filename);
    for (int i = 0; i < size; ++i) {
        fout << dis(gen);
        if (i != size - 1) {
            fout << " ";
        }
    }
    fout.close();
}
vector<int> loadArrayFromFile(const char* filename, int size) {
    vector<int> arr(size);
    ifstream fin(filename);
    for (int i = 0; i < size; ++i) {
        fin >> arr[i];
    }
    fin.close();
    return arr;
}


double measureAverageTime(const vector<int>& originalArr, void (*sortFunc)(vector<int>&)) {
    double totalDuration = 0;
    for (int run = 0; run < 3; ++run) {
        vector<int> tempArr = originalArr;
        auto start = chrono::high_resolution_clock::now();
        sortFunc(tempArr);
        auto end = chrono::high_resolution_clock::now();
        if (!isSorted(tempArr)) cout << "Îøèáêà ñîðòèðîâêè!" << endl;
        chrono::duration<double, milli> duration = end - start;
        totalDuration += duration.count();
    }
    return totalDuration / 3.0;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int sizes[3] = { 10000, 100000, 1000000 };
    int minVals[3] = { -10, -1000, -100000 };
    int maxVals[3] = { 10, 1000, 100000 };
    const char* filenames[3][3] = {
        {"array_10000_10.txt", "array_10000_1000.txt", "array_10000_100000.txt"},
        {"array_100000_10.txt", "array_100000_1000.txt", "array_100000_100000.txt"},
        {"array_1000000_10.txt", "array_1000000_1000.txt", "array_1000000_100000.txt"}
    };

    int mode;
    cin >> mode;
    if (mode == 0) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j)
            {
                generateAndSaveArray(sizes[i], minVals[j], maxVals[j], filenames[i][j]);
            }
        }
    }
    else {
        cout << "use from file" << endl;
    }

    cout << "Ðàçìåð\tÄèàïàçîí\tØåëëà (ìñ)\tÕèááàðä (ìñ)\tÊíóò (ìñ)\tÑåäæâèê (ìñ)" << endl;
    cout << "- - --- - - - -- - - - - - -- - - - - -- - - - - - - -- - - -" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            vector<int> currentArray = loadArrayFromFile(filenames[i][j], sizes[i]);
            double tOriginalShell = measureAverageTime(currentArray, shellSortOriginal);
            double tHibbard = measureAverageTime(currentArray, shellSortHibbard);
            double tKnuth = measureAverageTime(currentArray, shellSortKnuth);
            double tSedgewick = measureAverageTime(currentArray, shellSortSedgewick);
            cout << sizes[i] << "\t[" << minVals[j] << ";" << maxVals[j] << "]\t"
                << tOriginalShell << "\t\t" << tHibbard << "\t\t" << tKnuth << "\t\t" << tSedgewick << endl;
        }
    }
    return 0;
}