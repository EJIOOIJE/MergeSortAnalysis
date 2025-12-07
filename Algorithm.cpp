#include "Algorithm.h"

double Algorithm::generateFisk(double alpha, double c) {
    FiskGenerator gen;
    return gen.generateFisk(alpha, c);
}

std::vector<double> Algorithm::generateFiskArray(long long size, double alpha, double c) {
    FiskGenerator gen;
    return gen.generateFiskArray(size, alpha, c);
}

SortResult Algorithm::mergeSort(std::vector<double>& arr) {
    MergeSort<std::vector<double>::iterator> sort;
    return sort.sort(arr);
}

/*
#include "Algorithm.h"
#include <random>
#include <cmath>
#include <chrono>

using namespace std;

double Algorithm::generateFisk(double alpha, double c) {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_real_distribution<> dis(0.0, 1.0);

    double u = dis(gen);
    // избегать u == 0 или u == 1, чтобы избежать деления на 0
    if (u < 1e-15) u = 1e-15;
    if (u > 1 - 1e-15) u = 1 - 1e-15;

    // обратная функция преобразования
    double x = alpha * pow(u / (1 - u), 1.0 / c);

    return x;
}
*/
/*
    long long size размер массива
    double alpha = 1.0; шкала
    double c = 2.0; форма
*/
/*
vector<double> Algorithm::generateFiskArray(long long size, double alpha, double c) {
    vector<double> data(size);
    for (long long i = 0; i < size; ++i) {
        data[i] = generateFisk(alpha, c);
    }
    return data;
}

SortResult Algorithm::mergeSort(std::vector<double>& arr) {
    SortResult result;

    if (arr.empty()) return result;

    auto start = chrono::high_resolution_clock::now();
    mergeSortRecursive(arr, 0, static_cast<long long>(arr.size()) - 1, result);
    auto end = chrono::high_resolution_clock::now();

    result.elapsedTimeMs = end - start;

    return result;
}

void Algorithm::mergeSortRecursive(std::vector<double>& arr, long long left, long long right, SortResult& result) {
    if (left >= right) return;

    long long mid = left + (right - left) / 2;
    mergeSortRecursive(arr, left, mid, result);
    mergeSortRecursive(arr, mid + 1, right, result);
    mergeSortmerge(arr, left, mid, right, result);
}

void Algorithm::mergeSortmerge(std::vector<double>& arr, long long left, long long mid, long long right, SortResult& result) {
    long long n1 = mid - left + 1;
    long long n2 = right - mid;
    std::vector<double> L(n1);
    std::vector<double> R(n2);

    for (long long i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (long long j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    long long i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        result.comparisons++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
            result.swaps++;
        }
        else {
            arr[k++] = R[j++];
            result.swaps++;
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
        result.swaps++;
    }
    while (j < n2) {
        arr[k++] = R[j++];
        result.swaps++;
    }
}
*/