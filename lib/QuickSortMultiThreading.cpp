// QuickSortMultiThreading.cpp

#include "QuickSortMultiThreading.h"

// fonte codigo https://www.geeksforgeeks.org/quick-sort-using-multi-threading/

QuickSortMultiThreading::QuickSortMultiThreading(int start, int end, vector<int>& arr) 
    : start_(start), end_(end), arr_(arr) {}

int QuickSortMultiThreading::partition(int start, int end, vector<int>& arr) {
    int i = start;
    int j = end;

    // Escolhe um pivot aleatório
    int pivoted = rand() % (j - i + 1) + i;

    // Troca o pivot com o elemento final do array
    swap(arr[j], arr[pivoted]);
    j--;

    // Inicia o particionamento
    while (i <= j) {
        if (arr[i] <= arr[end]) {
            i++;
            continue;
        }
        if (arr[j] >= arr[end]) {
            j--;
            continue;
        }
        swap(arr[i], arr[j]);
        j--;
        i++;
    }

    // Coloca o pivot na posição correta
    swap(arr[j + 1], arr[end]);
    return j + 1;
}

void QuickSortMultiThreading::operator()() {
    // Caso base
    if (start_ >= end_) {
        return;
    }

    // Encontra a partição
    int p = partition(start_, end_, arr_);

    // Divide o array
    QuickSortMultiThreading left(start_, p - 1, arr_);
    QuickSortMultiThreading right(p + 1, end_, arr_);

    // Subproblemas da esquerda e direita como threads separadas
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            left();
        }
        #pragma omp section
        {
            right();
        }
    }
}