// QuickSortMultiThreading.h

#ifndef QUICKSORTMULTITHREADING_H
#define QUICKSORTMULTITHREADING_H

#include <vector>
#include <cstdlib> // Para rand()
#include <omp.h> // Para OpenMP

using namespace std;

class QuickSortMultiThreading {
public:
    QuickSortMultiThreading(int start, int end, vector<int>& arr);

    // Método para encontrar o pivot e particionar o array
    int partition(int start, int end, vector<int>& arr);

    // Método para implementar o QuickSort
    void operator()();

private:
    int start_;
    int end_;
    vector<int>& arr_;
};

#endif // QUICKSORTMULTITHREADING_H