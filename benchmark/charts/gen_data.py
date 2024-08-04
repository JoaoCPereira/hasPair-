import numpy as np

# Gera um vetor aleatório de tamanho `size` com valores no conjunto `C`.
def generate_vector(size, C, min_val, max_val, mid_value):
    vector = np.random.choice(C, size=size)
    vector[0] = vector[1] = min_val * 2  # Define os dois primeiros valores
    vector[-1] = vector[-2] = max_val * 2  # Define os dois últimos valores

    # Altera aleatoriamente dois valores, exceto os 2 primeiros e os 2 últimos
    middle_indices = range(2, size - 2)
    random_indices = np.random.choice(middle_indices, size=2, replace=False)
    vector[random_indices[0]] = mid_value
    vector[random_indices[1]] = mid_value

    return vector

# Converte um vetor em uma string no formato C++
def vector_to_cpp_string(vector_name, vector):
    vector_str = ','.join(map(str, vector))
    return f"vector<int> {vector_name} = {{{vector_str}}};\n"

# Gera um arquivo .cpp com definições de vetores de tamanhos especificados.
def generate_cpp_file(sizes, C, min_val, max_val, mid_value, cpp_file_path):
    with open(cpp_file_path, 'w') as cpp_file:
        cpp_file.write("#include <vector>\n\n")
        cpp_file.write("using namespace std;\n")
        
        for size in sizes:
            vector_name = f"input_{format_range(C)}_{size}"
            vector = generate_vector(size, C, min_val, max_val, mid_value)
            cpp_vector_str = vector_to_cpp_string(vector_name, vector)
            cpp_file.write(cpp_vector_str)
            cpp_file.write("\n")

# Gera um arquivo .h com declarações de vetores para uso em C++
def generate_header_file(sizes, C, header_file_path):
    with open(header_file_path, 'w') as header_file:
        header_file.write(f"// data_{format_range(C)}.h\n")
        header_file.write(f"#ifndef DATA_{format_range(C)}_H\n")
        header_file.write(f"#define DATA_{format_range(C)}_H\n\n")
        header_file.write("#include <vector>\n\n")
        header_file.write("using namespace std;\n")
        
        for size in sizes:
            vector_name = f"input_{format_range(C)}_{size}"
            header_file.write(f"extern vector<int> {vector_name};\n")
        
        header_file.write(f"\n#endif // DATA_{format_range(C)}_H\n")

# Formata o intervalo de `C` para ser utilizado nos nomes de arquivos e vetores.
# Substitui '-' por 'N' em números negativos.
def format_range(C):
    start = str(C[0]).replace('-', 'N')
    end = str(C[-1]).replace('-', 'N')
    return f"{start}_{end}"

def main():
    min_val = -32768
    max_val = 32768
    mid_value = 4512

    # Conjunto de valores (de -32768 a 32768)
    C = list(range(min_val, max_val))

    # Tamanhos dos vetores a serem gerados
    sizes = [16, 32, 128, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152]

    # Criar uma string a partir do intervalo de C usando a função format_range
    range_str = format_range(C)

    # Caminhos dos arquivos de saída
    cpp_file_path = f'../data_{range_str}.cpp'
    header_file_path = f'../data_{range_str}.h'

    # Gerar os arquivos .cpp e .h
    generate_cpp_file(sizes, C, min_val, max_val, mid_value, cpp_file_path)
    generate_header_file(sizes, C, header_file_path)

if __name__ == "__main__":
    main()
