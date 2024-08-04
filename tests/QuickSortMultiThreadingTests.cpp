#include <gtest/gtest.h>
#include "../lib/QuickSortMultiThreading.h"  // Inclua o cabeçalho da sua biblioteca
#include <vector>
#include <algorithm>  // std::sort para comparação

// Função auxiliar para verificar se o vetor está ordenado
bool is_sorted(const std::vector<int>& vec) {
    return std::is_sorted(vec.begin(), vec.end());
}

// Teste básico de ordenação
TEST(QuickSortMultiThreadingTest, SortsArrayCorrectly) {
    // Configurar dados de teste
    std::vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};

    QuickSortMultiThreading(0, arr.size() - 1, arr)();

    // Verificar se o vetor está ordenado
    EXPECT_TRUE(is_sorted(arr)) << "Array is not sorted correctly.";
}

// Teste com vetor vazio
TEST(QuickSortMultiThreadingTest, SortsEmptyArray) {
    std::vector<int> arr = {};

    QuickSortMultiThreading(0, arr.size() - 1, arr)();

    EXPECT_TRUE(is_sorted(arr)) << "Empty array is not sorted correctly.";
}

// Teste com vetor de um único elemento
TEST(QuickSortMultiThreadingTest, SortsSingleElementArray) {
    std::vector<int> arr = {42};

    QuickSortMultiThreading(0, arr.size() - 1, arr)();

    EXPECT_TRUE(is_sorted(arr)) << "Single element array is not sorted correctly.";
}

// Teste com vetor já ordenado
TEST(QuickSortMultiThreadingTest, HandlesAlreadySortedArray) {
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    QuickSortMultiThreading(0, arr.size() - 1, arr)();

    EXPECT_TRUE(is_sorted(arr)) << "Already sorted array is not sorted correctly.";
}

// Teste com vetor ordenado em ordem decrescente
TEST(QuickSortMultiThreadingTest, HandlesReverseSortedArray) {
    std::vector<int> arr = {9, 8, 7, 6, 5, 4, 3, 2, 1};

    QuickSortMultiThreading(0, arr.size() - 1, arr)();

    EXPECT_TRUE(is_sorted(arr)) << "Reverse sorted array is not sorted correctly.";
}

// Teste com números negativos
TEST(QuickSortMultiThreadingTest, HandlesNegativeNumbers) {
    std::vector<int> arr = {-3, -1, -4, -1, -5, -9, -2, -6, -5, -3, -5};

    QuickSortMultiThreading sorter(0, arr.size() - 1, arr);
    sorter();

    EXPECT_TRUE(is_sorted(arr)) << "Array with negative numbers is not sorted correctly.";
}

// Teste com números negativos e positivos
TEST(QuickSortMultiThreadingTest, HandlesMixedNumbers) {
    std::vector<int> arr = {3, -1, 4, -1, 5, -9, 2, 6, -5, 3, 5};

    QuickSortMultiThreading sorter(0, arr.size() - 1, arr);
    sorter();

    EXPECT_TRUE(is_sorted(arr)) << "Array with mixed numbers (negative and positive) is not sorted correctly.";
}

// Teste com vetor com todos os elementos iguais
TEST(QuickSortMultiThreadingTest, HandlesAllEqualElements) {
    std::vector<int> arr = {7, 7, 7, 7, 7, 7, 7};

    QuickSortMultiThreading sorter(0, arr.size() - 1, arr);
    sorter();

    EXPECT_TRUE(is_sorted(arr)) << "Array with all equal elements is not sorted correctly.";
}