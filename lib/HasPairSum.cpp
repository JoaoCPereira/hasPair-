// HasPairSum.cpp

#include "HasPairSum.h"

/**
 * @brief Retorna se existir algum par de inteiros em A[] cuja soma é x
 * 
 * Dado um vetor A[] de n inteiros e inteiro x, determine se existem
 * ou não dois elementos em A[] cuja soma é exatamente x.
 * 
*/

/*
 * Versão 1: Brute-force
 * @brief Verifica se existe um par de inteiros em A[] cuja soma é x
 * 
 * @param A vetor de inteiros
 * @param x inteiro
 * @return true se existir um par de inteiros em A[] cuja soma é x
 * @return false se não existir um par de inteiros em A[] cuja soma é x
*/
bool hasPairSum(vector<int> A, int x) {
    int n = A.size(); // Tamanho do vetor

    // Percorrer o vetor ate a posição N-1
    for (int i = 0; i < n-1; i++) {

        // Percorrer o vetor a partir da posição i+1
        for (int j = i+1; j < n; j++) {

            // caso a soma dos elementos A[i] e A[j] seja igual a x terminar a execução
            if (A[i] + A[j] == x) {
                return true;
            }
        }
    }
    return false;
}

/*
 * Versão 2: Brute-force com Threads (Função auxiliar)
 * 
 * @param A vetor de inteiros
 * @param x inteiro
 * @param found variável atômica que indica se a soma foi encontrada
 * @param coutMutex mutex para proteger a escrita no cout
 * @param start início do intervalo
 * @param end fim do intervalo
*/
void checkRange(const vector<int>& A, int x, atomic<bool>& found, mutex& coutMutex, int start, int end) {
    int n = A.size(); // Tamanho do vetor

    // Percorrer o intervalo designado para esta thread
    for (int i = start; i < end && !found.load(); ++i) {

        // Percorrer o vetor a partir da posição i+1
        for (int j = i + 1; j < n && !found.load(); ++j) {

            // Verificar se a soma dos elementos A[i] e A[j] é igual a x
            if (A[i] + A[j] == x) {

                // Bloquear o mutex antes de acessar o cout para evitar sobreposição de valores
                lock_guard<mutex> lock(coutMutex);

                // Sinalizar que um par foi encontrado
                found.store(true);
                return;
            }
        }
    }
}

/*
 * Versão 2: Brute-force com Threads
 * @brief Verifica se existe um par de inteiros em A[] cuja soma é x
 * 
 * @param A vetor de inteiros
 * @param x inteiro
 * @param t número de threads
 * @return true se existir um par de inteiros em A[] cuja soma é x
 * @return false se não existir um par de inteiros em A[] cuja soma é x
*/
bool hasPairSumThreads(const vector<int>& A, int x, int t) {
    int n = A.size(); // Tamanho do vetor
    atomic<bool> found(false); // Variável atômica para sinalizar se um par foi encontrado
    mutex coutMutex; // Mutex para sincronizar o acesso ao cout

    if (t <= 0) {
        t = 1; // Definir o número de threads como 1 se for inválido
    }

    vector<thread> threads; // Vetor para armazenar as threads
    int range = n / t; // Calcular o intervalo de elementos para cada thread

    // Criar e iniciar t threads
    for (int i = 0; i < t; ++i) {
        int start = i * range; // Indice inicial para a thread i
        int end = (i == t - 1) ? n : start + range; // Indice final, garantindo que a última thread vá até o final do vetor
        threads.emplace_back(checkRange, ref(A), x, ref(found), ref(coutMutex), start, end); // Criar e iniciar a thread
    }

    // Aguardar todas as threads
    for (auto& th : threads) {
        th.join();
    }

    return found.load(); // Retornar se um par foi encontrado
}

/*
 * Versão 3: Brute-force com vetor ordenado
 * @brief Verifica se existe um par de inteiros em A[] cuja soma é x
 * 
 * @param A vetor de inteiros
 * @param x inteiro
 * @return true se existir um par de inteiros em A[] cuja soma é x
 * @return false se não existir um par de inteiros em A[] cuja soma é x
*/
bool hasPairSumSorted(vector<int>& A, int X) {
    // Verifica se o vetor está vazio
    if (A.empty()) {
        return false; // Retorna false se o vetor estiver vazio
    }

    int n = A.size(); // Tamanho do vetor

    QuickSortMultiThreading(0, n - 1, A)(); // Ordena o vetor com a função QuickSortMultiThreading

    for (int i = 0; i < n && ((A[i] + A[i+1]) <= X) ; i++) {
        // Percorrer o vetor a partir da posição i+1
        for (int j = i-1; j < n && ((A[i] + A[j]) <= X); j++) {
            // caso a soma dos elementos A[i] e A[j] seja igual a x terminar a execução
            if (A[i] + A[j] == X) {
                return true;
            }
        }
    }

    return false; // Retorna false se não houver um par cuja soma seja igual a X
}

/*
 * Versão 4: BinarySearch com vetor ordenado (Função auxiliar)
 * 
 * @param A vetor de inteiros
 * @param start início do intervalo
 * @param end fim do intervalo
 * @param target inteiro
 * @return true se encontrar o target no vetor
 * @return false se não encontrar o target no vetor
*/
bool binarySearch(const vector<int>& A, int start, int end, int target) {
    // enquanto o início for menor ou igual ao fim
    while (start <= end) {
        // encontrar o meio do vetor
        int mid = start + (end - start) / 2;

        // Verificar se o target é iagual ao elemento do meio
        if (A[mid] == target) {
            return true;
        // Verificar se o target é maior que o elemento do meio, se sim, ignorar a metade esquerda
        } else if (A[mid] < target) {
            start = mid + 1;
        } else { // Se o target for menor que o elemento do meio, ignorar a metade direita
            end = mid - 1;
        }
    }
    return false;
}

/*
 * Versão 4: BinarySearch com vetor ordenado
 * @brief Verifica se existe um par de inteiros em A[] cuja soma é x
 * 
 * @param A vetor de inteiros
 * @param x inteiro
 * @return true se existir um par de inteiros em A[] cuja soma é x
 * @return false se não existir um par de inteiros em A[] cuja soma é x
*/
bool hasPairSumSortedBinarySearch(vector<int>& A, int X) {
    if (A.empty()) {
        return false;
    }

    int n = A.size(); // Tamanho do vetor

    QuickSortMultiThreading(0, n - 1, A)(); // Ordena o vetor com a função QuickSortMultiThreading

    // Percorre o vetor e usa busca binária para encontrar o complemento
    for (int i = 0; i < n && (A[i] + A[i+1] < X); ++i) {
        int complement = X - A[i];
        // procurar o complemento no vetor
        if (binarySearch(A, i + 1, n - 1, complement)) {
            return true;
        }
    }
    return false;
}

/*
 * Versão 5: BinarySearch com Threads (Função auxiliar)
 * @brief Verifica se existe um par de inteiros em A[] cuja soma é x
 * 
 * @param A vetor de inteiros
 * @param x inteiro
 * @param found variável atômica que indica se a soma foi encontrada
 * @param coutMutex mutex para proteger a impressão
 * @param start início do intervalo
 * @param end fim do intervalo
*/
void checkRangeBinarySearch(const vector<int>& A, int x, atomic<bool>& found, mutex& coutMutex, int start, int end) {
    int n = A.size(); // Tamanho do vetor

    // Percorrer o intervalo designado para esta thread
    for (int i = start; i < end && !found.load() && (A[i] + A[i+1] < x); ++i) {
        int complement = x - A[i];

        if (binarySearch(A, i + 1, n - 1, complement)) {
            // Bloquear o mutex antes de acessar o cout para evitar sobreposição de valores
            lock_guard<mutex> lock(coutMutex);

            // Sinalizar que um par foi encontrado
            found.store(true);
            return;
        }
    }
}

/*
 * Versão 5: BinarySearch com Threads
 * @brief Verifica se existe um par de inteiros em A[] cuja soma é x
 * 
 * @param A vetor de inteiros
 * @param x inteiro
 * @param t número de threads
 * @return true se existir um par de inteiros em A[] cuja soma é x
 * @return false se não existir um par de inteiros em A[] cuja soma é x
*/
bool hasPairSumSortedBinarySearchThreads(vector<int>& A, int X, int t) {
    int n = A.size(); // Tamanho do vetor
    atomic<bool> found(false); // Variável atômica para sinalizar se um par foi encontrado
    mutex coutMutex; // Mutex para sincronizar o acesso ao cout

    if (A.empty()) {
        return false;
    }

    if (t <= 0) {
        t = 1; // Definir o número de threads como 1 se for inválido
    }

    vector<thread> threads; // Vetor para armazenar as threads
    int range = n / t; // Calcular o intervalo de elementos para cada thread

    QuickSortMultiThreading(0, n - 1, A)(); // Ordena o vetor com a função QuickSortMultiThreading

    // Criar e iniciar t threads
    for (int i = 0; i < t; ++i) {
        int start = i * range; // Indice inicial para esta thread
        int end = (i == t - 1) ? n : start + range; // Indice final, garantindo que a última thread vá até o final do vetor
        threads.emplace_back(checkRangeBinarySearch, ref(A), X, ref(found), ref(coutMutex), start, end); // Criar e iniciar a thread
    }

    // Aguardar todas as threads
    for (auto& th : threads) {
        th.join();
    }

    return found.load(); // Retornar se um par foi encontrado
}