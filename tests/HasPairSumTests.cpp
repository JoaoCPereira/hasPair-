#include <gtest/gtest.h>
#include "../lib/HasPairSum.h"

using namespace std;

/*
    hasPairSum - Versão 1
*/

// Teste hasPairSum lista vazia
TEST(hasPairSum, ListaVazia) {
    vector<int> A = {};
    EXPECT_FALSE(hasPairSum(A, -5)); // Não há par que some -5
    EXPECT_FALSE(hasPairSum(A, 0)); // Não há par que some -0
}

// Teste hasPairSum soma positiva lista não vazia
TEST(hasPairSum, SomaPositiva) {
    vector<int> A = {1, 2, 3, 4, 5, -2, -1};
    EXPECT_TRUE(hasPairSum(A, 8)); // Deve encontrar o par (3, 5)
    EXPECT_TRUE(hasPairSum(A, 9)); // Deve encontrar o par (4, 5)
    EXPECT_FALSE(hasPairSum(A, 10)); // Não há par que some 10
    EXPECT_FALSE(hasPairSum(A, -4)); // Não há par que some -4
}

// Teste hasPairSum soma negativa lista não vazia
TEST(hasPairSum, SomaNegativa) {
    vector<int> A = {1, 2, 3, 4, 5, -2, -1};
    EXPECT_TRUE(hasPairSum(A, -3)); // Deve encontrar o par (-2, -1)
    EXPECT_TRUE(hasPairSum(A, 1)); // Deve encontrar o par (3, -2) ou (2, -1)
    EXPECT_FALSE(hasPairSum(A, -4)); // Não há par que some -4
    EXPECT_FALSE(hasPairSum(A, 10)); // Não há par que some 10
}

/*
    hasPairSumThreads - Versão 2
*/

// Teste hasPairSumThreads lista vazia
TEST(hasPairSumThreads, ListaVazia) {
    vector<int> A = {};
    EXPECT_FALSE(hasPairSumThreads(A, -5, 1)); // Não há par que some -5
    EXPECT_FALSE(hasPairSumThreads(A, 0, 2)); // Não há par que some -0
}

// Teste hasPairSumThreads soma positiva lista não vazia
TEST(hasPairSumThreads, SomaPositiva) {
    vector<int> A = {1, 2, 3, 4, 5, -2, -1};
    EXPECT_TRUE(hasPairSumThreads(A, 8, 3)); // Deve encontrar o par (3, 5)
    EXPECT_TRUE(hasPairSumThreads(A, 9, 4)); // Deve encontrar o par (4, 5)
    EXPECT_FALSE(hasPairSumThreads(A, 10, 1)); // Não há par que some 10
    EXPECT_FALSE(hasPairSumThreads(A, -4, 6)); // Não há par que some -4
}

// Teste hasPairSumThreads soma negativa lista não vazia
TEST(hasPairSumThreads, SomaNegativa) {
    vector<int> A = {1, 2, 3, 4, 5, -2, -1};
    EXPECT_TRUE(hasPairSumThreads(A, -3, 3)); // Deve encontrar o par (-2, -1)
    EXPECT_TRUE(hasPairSumThreads(A, 1, 4)); // Deve encontrar o par (3, -2) ou (2, -1)
    EXPECT_FALSE(hasPairSumThreads(A, -4, 2)); // Não há par que some -4
    EXPECT_FALSE(hasPairSumThreads(A, 10, 1)); // Não há par que some 10
}

// Teste hasPairSumThreads numero threads negativo
TEST(hasPairSumThreads, NumeroThreadsNegativo) {
    vector<int> A = {1, 2, 3, 4, 5, -2, -1};
    EXPECT_TRUE(hasPairSumThreads(A, -3, -1)); // Deve encontrar o par (-2, -1)
    EXPECT_TRUE(hasPairSumThreads(A, 1, -2)); // Deve encontrar o par (3, -2) ou (2, -1)
    EXPECT_FALSE(hasPairSumThreads(A, -4, -3)); // Não há par que some -4
    EXPECT_FALSE(hasPairSumThreads(A, 10, -4)); // Não há par que some 10
}

// Teste hasPairSumThreads numero threads superior ao tamanho do vetor/ threads disponiveis
TEST(hasPairSumThreads, NumeroThreadsSuperior) {
    vector<int> A = {1, 2, 3, 4, 5, -2, -1};
    EXPECT_TRUE(hasPairSumThreads(A, -3, 32)); // Deve encontrar o par (-2, -1)
    EXPECT_TRUE(hasPairSumThreads(A, 1, 64)); // Deve encontrar o par (3, -2) ou (2, -1)
    EXPECT_FALSE(hasPairSumThreads(A, -4, 128)); // Não há par que some -4
    EXPECT_FALSE(hasPairSumThreads(A, 10, 256)); // Não há par que some 10
}

/*
    hasPairSumSorted - Versão 3
*/

// Teste hasPairSumSorted lista vazia
TEST(hasPairSumSorted, ListaVazia) {
    vector<int> A = {};
    EXPECT_FALSE(hasPairSumSorted(A, -5)); // Não há par que some -5
    EXPECT_FALSE(hasPairSumSorted(A, 0)); // Não há par que some -0
}

// Teste hasPairSumSorted soma positiva lista não vazia
TEST(hasPairSumSorted, SomaPositiva) {
    vector<int> A = {1, 2, 3, 4, 5, -2, -1};
    EXPECT_TRUE(hasPairSumSorted(A, 8)); // Deve encontrar o par (3, 5)
    EXPECT_TRUE(hasPairSumSorted(A, 9)); // Deve encontrar o par (4, 5)
    EXPECT_FALSE(hasPairSumSorted(A, 10)); // Não há par que some 10
    EXPECT_FALSE(hasPairSumSorted(A, -4)); // Não há par que some -4
}

// Teste hasPairSumSorted soma negativa lista não vazia
TEST(hasPairSumSorted, SomaNegativa) {
    vector<int> A = {1, 2, 3, 4, 5, -2, -1};
    EXPECT_TRUE(hasPairSumSorted(A, -3)); // Deve encontrar o par (-2, -1)
    EXPECT_TRUE(hasPairSumSorted(A, 1)); // Deve encontrar o par (3, -2) ou (2, -1)
    EXPECT_FALSE(hasPairSumSorted(A, -4)); // Não há par que some -4
    EXPECT_FALSE(hasPairSumSorted(A, 10)); // Não há par que some 10
}

/*
    hasPairSumSortedBinarySearch - Versão 4
*/

// Teste hasPairSumSortedBinarySearch lista vazia
TEST(hasPairSumSortedBinarySearch, ListaVazia) {
    vector<int> A = {};
    EXPECT_FALSE(hasPairSumSortedBinarySearch(A, -5)); // Não há par que some -5
    EXPECT_FALSE(hasPairSumSortedBinarySearch(A, 0)); // Não há par que some -0
}

// Teste hasPairSumSortedBinarySearch soma positiva lista não vazia
TEST(hasPairSumSortedBinarySearch, SomaPositiva) {
    vector<int> A = {1, 2, 3, 4, 5, -2, -1};
    EXPECT_TRUE(hasPairSumSortedBinarySearch(A, 8)); // Deve encontrar o par (3, 5)
    EXPECT_TRUE(hasPairSumSortedBinarySearch(A, 9)); // Deve encontrar o par (4, 5)
    EXPECT_FALSE(hasPairSumSortedBinarySearch(A, 10)); // Não há par que some 10
    EXPECT_FALSE(hasPairSumSortedBinarySearch(A, -4)); // Não há par que some -4
}

// Teste hasPairSumSortedBinarySearch soma negativa lista não vazia
TEST(hasPairSumSortedBinarySearch, SomaNegativa) {
    vector<int> A = {1, 2, 3, 4, 5, -2, -1};
    EXPECT_TRUE(hasPairSumSortedBinarySearch(A, -3)); // Deve encontrar o par (-2, -1)
    EXPECT_TRUE(hasPairSumSortedBinarySearch(A, 1)); // Deve encontrar o par (3, -2) ou (2, -1)
    EXPECT_FALSE(hasPairSumSortedBinarySearch(A, -4)); // Não há par que some -4
    EXPECT_FALSE(hasPairSumSortedBinarySearch(A, 10)); // Não há par que some 10
}

/*
    hasPairSumSortedBinarySearchThreads - Versão 5
*/

// Teste hasPairSumSortedBinarySearchThreads lista vazia
TEST(hasPairSumSortedBinarySearchThreads, ListaVazia) {
    vector<int> A = {};
    EXPECT_FALSE(hasPairSumSortedBinarySearchThreads(A, -5, 1)); // Não há par que some -5
    EXPECT_FALSE(hasPairSumSortedBinarySearchThreads(A, 0, 2)); // Não há par que some -0
}

// Teste hasPairSumSortedBinarySearchThreads soma positiva lista não vazia
TEST(hasPairSumSortedBinarySearchThreads, SomaPositiva) {
    vector<int> A = {1, 2, 3, 4, 5, -2, -1};
    EXPECT_TRUE(hasPairSumSortedBinarySearchThreads(A, 8, 3)); // Deve encontrar o par (3, 5)
    EXPECT_TRUE(hasPairSumSortedBinarySearchThreads(A, 9, 4)); // Deve encontrar o par (4, 5)
    EXPECT_FALSE(hasPairSumSortedBinarySearchThreads(A, 10, 1)); // Não há par que some 10
    EXPECT_FALSE(hasPairSumSortedBinarySearchThreads(A, -4, 6)); // Não há par que some -4
}

// Teste hasPairSumSortedBinarySearchThreads soma negativa lista não vazia
TEST(hasPairSumSortedBinarySearchThreads, SomaNegativa) {
    vector<int> A = {1, 2, 3, 4, 5, -2, -1};
    EXPECT_TRUE(hasPairSumSortedBinarySearchThreads(A, -3, 3)); // Deve encontrar o par (-2, -1)
    EXPECT_TRUE(hasPairSumSortedBinarySearchThreads(A, 1, 4)); // Deve encontrar o par (3, -2) ou (2, -1)
    EXPECT_FALSE(hasPairSumSortedBinarySearchThreads(A, -4, 2)); // Não há par que some -4
    EXPECT_FALSE(hasPairSumSortedBinarySearchThreads(A, 10, 1)); // Não há par que some 10
}

// Teste hasPairSumSortedBinarySearchThreads numero threads negativo
TEST(hasPairSumSortedBinarySearchThreads, NumeroThreadsNegativo) {
    vector<int> A = {1, 2, 3, 4, 5, -2, -1};
    EXPECT_TRUE(hasPairSumSortedBinarySearchThreads(A, -3, -1)); // Deve encontrar o par (-2, -1)
    EXPECT_TRUE(hasPairSumSortedBinarySearchThreads(A, 1, -2)); // Deve encontrar o par (3, -2) ou (2, -1)
    EXPECT_FALSE(hasPairSumSortedBinarySearchThreads(A, -4, -3)); // Não há par que some -4
    EXPECT_FALSE(hasPairSumSortedBinarySearchThreads(A, 10, -4)); // Não há par que some 10
}

// Teste hasPairSumThreads numero threads superior ao tamanho do vetor/ threads disponiveis
TEST(hasPairSumSortedBinarySearchThreads, NumeroThreadsSuperior) {
    vector<int> A = {1, 2, 3, 4, 5, -2, -1};
    EXPECT_TRUE(hasPairSumSortedBinarySearchThreads(A, -3, 32)); // Deve encontrar o par (-2, -1)
    EXPECT_TRUE(hasPairSumSortedBinarySearchThreads(A, 1, 64)); // Deve encontrar o par (3, -2) ou (2, -1)
    EXPECT_FALSE(hasPairSumSortedBinarySearchThreads(A, -4, 128)); // Não há par que some -4
    EXPECT_FALSE(hasPairSumSortedBinarySearchThreads(A, 10, 256)); // Não há par que some 10
}


/*
Aux functions
*/

// Test para binarySearch
TEST(binarySearch, BinarySearchTests) {
    vector<int> A1 = {1, 2, 3, 4, 5};
    EXPECT_TRUE(binarySearch(A1, 0, A1.size(), 1));
    EXPECT_TRUE(binarySearch(A1, 0, 3, 2));
    EXPECT_FALSE(binarySearch(A1, 0, A1.size(), 6));

    vector<int> A2 = {1, 3, 5, 7, 9};
    EXPECT_TRUE(binarySearch(A2, 0, A2.size(), 9));
    EXPECT_FALSE(binarySearch(A2, 0, A2.size(), 2));
}