#include <chrono>
#include <omp.h>
#include "lib/hasPairSum.h"

using namespace std;

int main() {
    vector<int> A = { 1, 4, 45, 45, 5, 67, 77, 8, 2, -3, 321, 542, -66, 100, 200};
 
    if (hasPairSumSortedBinarySearch(A, 10)) {
        cout << "Soma encontrada!";
    } else {
        cout << "Soma não encontrada!";
    }

    return 0;
}