# Define a versão mínima necessária do CMake para este projeto
cmake_minimum_required(VERSION 3.11)

# Define o projeto com o nome "MainProject", versão 1.0.0 e linguagem C++
project(MainProject VERSION 1.0.0 LANGUAGES CXX)

# Inclui o módulo FetchContent para facilitar o download e inclusão de conteúdo externo
include(FetchContent)

# Declara que queremos descarregar o GoogleTest utilizando FetchContent
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true  # Mantém o timestamp de extração
)

# Configura o GoogleTest para usar o CRT (C Run-Time) partilhado, no contexto do Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Descarrega e prepara o GoogleTest para ser utilizado no projeto
FetchContent_MakeAvailable(googletest)

# Criar a biblioteca "QuickSortMultiThreading"
add_library(QuickSortMultiThreading
    lib/QuickSortMultiThreading.cpp
)

# Criar a biblioteca "HasPairSum"
add_library(HasPairSum
    lib/HasPairSum.cpp
)

# Criar a biblioteca "Data"
add_library(Data
    benchmark/data.cpp
    benchmark/data_N32768_32767.cpp
)

# Liga a biblioteca "QuickSortMultiThreading" como dependência privada à biblioteca "HasPairSum"
target_link_libraries(HasPairSum
    PRIVATE QuickSortMultiThreading
)

# Cria o executável "MainProject" a partir do ficheiro de código-fonte principal
add_executable(MainProject main.cpp)

# Liga as bibliotecas "QuickSortMultiThreading" e "HasPairSum" como dependências privadas ao executável "MainProject"
target_link_libraries(MainProject
    PRIVATE QuickSortMultiThreading
    PRIVATE HasPairSum
)

# Define o padrão C++ para o executável "MainProject" como C++17
set_property(TARGET MainProject PROPERTY CXX_STANDARD 17)

# Incluir o módulo GoogleTest para facilitar a integração com testes escritos utilizando GoogleTest
include(GoogleTest)

# Verificar se o ficheiro de testes para "QuickSortMultiThreading" existe e, se existir, configurar os testes
if(EXISTS "${CMAKE_SOURCE_DIR}/tests/QuickSortMultiThreadingTests.cpp")
    # Criar o executável de teste "QuickSortMultiThreadingTests"
    add_executable(QuickSortMultiThreadingTests "tests/QuickSortMultiThreadingTests.cpp")

    # Ligar a biblioteca "gtest_main" e "QuickSortMultiThreading"
    target_link_libraries(QuickSortMultiThreadingTests
        PRIVATE gtest_main
        PRIVATE QuickSortMultiThreading
    )

    # Descobrir e registar automaticamente os testes do executável "QuickSortMultiThreadingTests"
    gtest_discover_tests(QuickSortMultiThreadingTests)
else()
    # Exibe uma mensagem se o ficheiro de testes não for encontrado
    message(STATUS "No QuickSortMultiThreadingTests.cpp files found. Skipping test configuration.")
endif()

# Verifica se o ficheiro de testes para "HasPairSum" existe e, se existir, configurar os testes
if(EXISTS "${CMAKE_SOURCE_DIR}/tests/HasPairSumTests.cpp")
    # Criar o executável de teste "HasPairSumTests"
    add_executable(HasPairSumTests "tests/HasPairSumTests.cpp")

    # Ligar as bibliotecas "gtest_main", "QuickSortMultiThreading" e "HasPairSum"
    target_link_libraries(HasPairSumTests
        PRIVATE gtest_main
        PRIVATE QuickSortMultiThreading
        PRIVATE HasPairSum
    )

    # Descobrir e registar automaticamente os testes do executável "HasPairSumTests"
    gtest_discover_tests(HasPairSumTests)
else()
    # Exibe uma mensagem se o ficheiro de testes não for encontrado
    message(STATUS "No HasPairSumTests.cpp files found. Skipping test configuration.")
endif()

# Adicionar o executável "Benchmark"
add_executable(Benchmark benchmark/benchmark.cpp)

# Ligar as bibliotecas "HasPairSum", "QuickSortMultiThreading" e "Data" como dependências privadas ao executável "Benchmark"
target_link_libraries(Benchmark
    PRIVATE HasPairSum
    PRIVATE QuickSortMultiThreading
    PRIVATE Data
)
