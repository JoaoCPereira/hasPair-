// benchmark/benchmark.cpp
#include <iostream>
#include <vector>
#include <chrono>
#include <functional>
#include <fstream>
#include <filesystem>
#include <sstream>
#include "../lib/HasPairSum.h"
#include "data.h"
#include "data_N32768_32767.h"

using namespace std;
namespace fs = filesystem;

// Função de benchmark genérica para funções
template <typename Func>
void benchmarkFunction(int iteracao, const string& name, const bool resultado_esperado, const string& caso, 
                       const Func& func, const vector<int>& data, int x) {
    vector<int> input_data = data;

    auto start = chrono::high_resolution_clock::now();
    bool result = func(input_data, x);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << iteracao << ", " << name << ", " << resultado_esperado << ", " << result << ", " << data.size() 
         << ", " << duration << ", " << caso << endl;
}

// Função de benchmark específica para funções com threads
template <typename Func>
void benchmarkFunctionThreads(int iteracao, const string& name, const bool resultado_esperado, const string& caso, 
                              const Func& func, const vector<int>& data, int x, int t) {
    vector<int> input_data = data;

    auto start = chrono::high_resolution_clock::now();
    bool result = func(input_data, x, t);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << iteracao << ", " << name << ", " << resultado_esperado << ", " << result << ", " << data.size() 
         << ", " << duration << ", " << caso << endl;
}

// Função que imprime um vetor no formato "{elementos};"
void printVector(const vector<int>& data) {
    cout << "{";
    for (size_t i = 0; i < data.size(); ++i) {
        cout << data[i];
        if (i < data.size() - 1) {
            cout << ", ";
        }
    }
    cout << "};" << endl;
}

void benchmarkRun(int n, int t, int x, const vector<int>& input_data, bool resultado_esperado, const string& caso) {
    for (int i = 0; i < n; i++) {

        // Executar benchmarks
        if (input_data.size() <= 32768 || resultado_esperado == true) {
            benchmarkFunction(i, "hasPairSum", resultado_esperado, caso, hasPairSum, input_data, x);
            benchmarkFunction(i, "hasPairSumSorted", resultado_esperado, caso, hasPairSumSorted, input_data, x);
        }
        if (input_data.size() <= 131072 || resultado_esperado == true) {
            benchmarkFunctionThreads(i, "hasPairSumThreads", resultado_esperado, caso, hasPairSumThreads, input_data, x, t);
        }
        benchmarkFunction(i, "hasPairSumSortedBinarySearch", resultado_esperado, caso, hasPairSumSortedBinarySearch, input_data, x);
        benchmarkFunctionThreads(i, "hasPairSumSortedBinarySearchThreads", resultado_esperado, caso, hasPairSumSortedBinarySearchThreads, input_data, x, t);
    }
}

void executarBenchmark(int numeroIteracoes, int numeroThreads, const vector<vector<int>*>& inputs, const vector<int>& xs, const vector<bool>& resultadosEsperados, const vector<string>& casos) {
    for (size_t i = 0; i < xs.size(); ++i) {
        for (auto input : inputs) {
            benchmarkRun(numeroIteracoes, numeroThreads, xs[i], *input, resultadosEsperados[i], casos[i]);
        }
    }
}

string construirCaminhoDoArquivo(int numeroIteracoes) {
    ostringstream oss;
    oss << "../benchmark/new_[N32768_32767]_output_" << numeroIteracoes << ".txt";
    return oss.str();
}

void inicializarArquivoSaida(const string& filePath) {
    ofstream outFile(filePath, ios::app);
    if (!outFile.is_open()) {
        cerr << "Não foi possível abrir o arquivo para escrita." << endl;
        exit(1);
    }

    // Verificar se o arquivo está vazio ou não existe
    bool isEmpty = !fs::exists(filePath) || fs::file_size(filePath) == 0;

    // Imprimir cabeçalho se o arquivo estiver vazio
    if (isEmpty) {
        outFile << "Numero Iteração, Nome função, Resultado esperado, Resultado, Tamanho vector, Tempo execução (nanosegundos), Caso" << endl;
    }

    outFile.close();
}

void body() {
    const int numeroIteracoes = 500;
    const int numeroThreads = 28;

    vector<int> xs = {-131072, 262144};
    vector<bool> resultadosEsperados = {true, false};
    vector<string> casos = {
        "Melhor Caso BF (A[0] + A[1] == x)",
        "Pior caso x !C A",
    };
    
    vector<vector<int>*> inputs = {
        &input_N32768_32767_16,
        &input_N32768_32767_32,
        &input_N32768_32767_128,
        &input_N32768_32767_512,
        &input_N32768_32767_1024,
        &input_N32768_32767_2048,
        &input_N32768_32767_4096,
        &input_N32768_32767_8192,
        &input_N32768_32767_16384,
        &input_N32768_32767_32768,
        &input_N32768_32767_65536,
        &input_N32768_32767_131072,
        &input_N32768_32767_262144,
        &input_N32768_32767_524288,
        &input_N32768_32767_1048576,
        &input_N32768_32767_2097152
    };

    string filePath = construirCaminhoDoArquivo(numeroIteracoes);

    inicializarArquivoSaida(filePath);

    // Redirecionar cout para o arquivo
    ofstream outFile(filePath, ios::app);
    streambuf* originalBuf = cout.rdbuf();
    cout.rdbuf(outFile.rdbuf());

    // Executar benchmarks
    executarBenchmark(numeroIteracoes, numeroThreads, inputs, xs, resultadosEsperados, casos);

    // Restaurar cout para o console
    cout.rdbuf(originalBuf);

    // Fechar o arquivo
    outFile.close();
}

int main() {
    // Iniciar a medição do tempo de execução
    auto start = chrono::high_resolution_clock::now();

    body();

    // Parar a medição do tempo de execução
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(end - start).count();

    // Calcular horas, minutos e segundos
    int hours = duration / 3600;
    int minutes = (duration % 3600) / 60;
    int seconds = duration % 60;

    // Imprimir a duração no formato hh:mm:ss
    cout << "Tempo total de execução: "
        << (hours < 10 ? "0" : "") << hours << ":"
        << (minutes < 10 ? "0" : "") << minutes << ":"
        << (seconds < 10 ? "0" : "") << seconds << endl;

    return 0;
}