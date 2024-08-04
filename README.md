# Comparação e Otimização da Função **hasPair()**

> **Nota:**  
> A função `hasPair()` recebe como parâmetros um vetor `A[]` de `N` inteiros e um inteiro `x`, e determina se existem ou não dois elementos em `A` cuja soma é exatamente `x`.

## Implementações

### Versão 1 (**hasPairSum()**)
- **Força Bruta**
- Não ordena o vetor.
- Percorre o vetor da posição 0 até N, verificando se a soma de qualquer par de valores é igual a `x`.

### Versão 2 (**hasPairSumThreads()**)
- **Força Bruta com Threads**
- Não ordena o vetor.
- Recebe um terceiro parâmetro: o número de threads (a gestão das threads consome algum tempo).
- Divide o vetor entre as threads; as threads "partilham" um valor booleano. Quando uma thread encontra um par cuja soma seja igual a `x`, todas as threads terminam.

### Versão 3 (**hasPairSumSorted()**)
- **Força Bruta com Vetor Ordenado**
- Ordena o vetor utilizando a função `QuickSortMultiThreading` (ordenar o vetor consome algum tempo).
- Percorre o vetor da posição 0 até N, verificando se a soma dos valores é igual a `x`. Como o vetor é ordenado, se o valor de `A[i] + A[j] > x`, onde `j > i`, a função retorna `false`.

### Versão 4 (**hasPairSumSortedBinarySearch()**)
- **Pesquisa Binária**
- Ordena o vetor utilizando a função `QuickSortMultiThreading` (ordenar o vetor consome algum tempo).
- Percorre o vetor da posição 0 até N. Para cada elemento, calcula o seu complementar e procura por esse elemento usando uma função de pesquisa binária. Caso `A[i] + A[i+1] > x`, a função retorna `false`.

### Versão 5 (**hasPairSumSortedBinarySearchThreads()**)
- **Pesquisa Binária com Threads**
- Ordena o vetor utilizando a função `QuickSortMultiThreading` (ordenar o vetor consome algum tempo).
- Recebe um terceiro parâmetro: o número de threads (a gestão das threads consome algum tempo).
- Divide o vetor entre as threads; as threads "partilham" um valor booleano. Quando uma thread encontra um par cuja soma seja igual a `x`, todas as threads terminam. Cada thread calcula o complementar e procura por esse elemento usando uma função de pesquisa binária. Caso `A[i] + A[i+1] > x`, a função retorna `false`.

## Build
1. mkdir build
2. cd build
3. cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE --no-warn-unused-cli -G "Unix Makefiles" ..
4.1 cmake --build . --target MainProject
4.2 cmake --build . --target HasPairSumTests
4.3 cmake --build . --target Benchmark
4.4 cmake --build . --target all

## Informações do Sistema

- **Sistema Operativo**
  - Windows 11 Home
  - Versão 23H2

- **Processador**
  - Intel Core i7 14700K
  - Núcleos: 20 (8 P-cores + 12 E-cores)
  - Threads: 28

- **Memória RAM**
  - Total: 64GB (5200 MHz)
  - Módulos:
    - 4x Corsair 16GB CMK32GX5M2X7200C34 

- **Placa Gráfica**
  - NVIDIA GeForce RTX 4080 SUPER

## Benchmark

### Melhor Caso: A[0] + A[1] == x

| ![Melhor caso (versão 1), A[0]+A[1] == x, log](benchmark/charts/img/execution_time_Melhor_Caso_BF_A[0]_+_A[1]_==_x_log.png "Melhor caso (versão 1), A[0]+A[1] == x, escala logarítmica") | ![Melhor caso (versão 1), A[0]+A[1] == x](benchmark/charts/img/execution_time_Melhor_Caso_BF_A[0]_+_A[1]_==_x.png "Melhor caso (versão 1), A[0]+A[1] == x") |
|------------------------------------------------------------|------------------------------------------------------------|

> Ao comparar os valores médios para um vetor `A` não ordenado de tamanho 2097152, verifica-se a perda de performance devido ao processo de ordenação e gestão das threads.  
> [Tabela melhor caso, A.size() == 2097152](benchmark/charts/img/execution_time_table[2097152]-_Melhor_Caso_BF_A[0]_+_A[1]_==_x.png "Tabela melhor caso, A.size() == 2097152")

### Pior Caso: Não existem **\(i\) e \(j\) tais que \(A[i] + A[j] = x\)**

| ![Pior caso: não existem **\(i\) e \(j\) tais que \(A[i] + A[j] = x\)**, log](benchmark/charts/img/execution_time_Pior_caso_x_NC_A_log.png "Pior caso: não existem **\(i\) e \(j\) tais que \(A[i] + A[j] = x\)**, escala logarítmica") | ![Pior caso: não existem **\(i\) e \(j\) tais que \(A[i] + A[j] = x\)**](benchmark/charts/img/execution_time_Pior_caso_x_NC_A.png "Pior caso: não existem **\(i\) e \(j\) tais que \(A[i] + A[j] = x\)**") |
|------------------------------------------------------------|------------------------------------------------------------|

> Ao comparar os valores médios para um vetor `A` não ordenado de tamanho 32768, verifica-se que a versão 1 e 3 já têm bastante dificuldade em executar em tempo útil. A versão 2 começa a ter algumas dificuldades. Não existem diferenças significativas entre a versão 4 e 5, mas ainda se nota a perda de performance da versão 5 devido à gestão das threads.  
> [Pior caso, A.size() == 32768](benchmark/charts/img/execution_time_table[32768]-_Pior_caso_x_NC_A.png "Pior caso, A.size() == 32768")

> Ao comparar os valores médios para um vetor `A` não ordenado de tamanho 131072, verifica-se que a versão 3 já tem bastante dificuldade em executar em tempo útil. A versão 5 começa a ter uma pequena vantagem sobre a versão sem threads.  
> [Pior caso, A.size() == 131072](benchmark/charts/img/execution_time_table[131072]-_Pior_caso_x_NC_A.png "Pior caso, A.size() == 131072")

> Ao comparar os valores médios para um vetor `A` não ordenado de tamanho 2097152, já se nota uma vantagem significativa das versões com threads.  
> [Pior caso, A.size() == 2097152](benchmark/charts/img/execution_time_table[2097152]-_Pior_caso_x_NC_A.png "Pior caso, A.size() == 2097152")
